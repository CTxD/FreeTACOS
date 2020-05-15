#include <apex_mutex.hpp>
#include <apex_types.hpp>
#include <partitionscheduling.hpp>
#include <process_schedule.hpp>
#include <arinc_module.hpp>
#include <arch.h>
#include <vector>
#include <queue>
#include <cstdlib>

std::vector<PartitionMutex> ApexMutex::partitionMutexes{};

int ApexMutex::getMutexAmount(){
    int numberOfMutexes = 0;
    for (auto& partitionMutex : partitionMutexes){
        numberOfMutexes += partitionMutex.mutexes.size();
    }
    return numberOfMutexes;
}

/**
 * @brief Creates a mutex
 *
 * @param MUTEX_NAME
 * @param MUTEX_PRIORITY
 * @param QUEUING_DISCIPLINE
 * @param MUTEX_ID
 * @param RETURN_CODE
 */
void ApexMutex::CREATE_MUTEX(
    /*in */ MUTEX_NAME_TYPE MUTEX_NAME,
    /*in */ PRIORITY_TYPE MUTEX_PRIORITY,
    /*in */ QUEUING_DISCIPLINE_TYPE QUEUING_DISCIPLINE,
    /*out*/ MUTEX_ID_TYPE* MUTEX_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE){

    auto* currentPartition = CyclicExecutiveSchedule::getCurrentPartition();

    if(currentPartition->operatingMode == OPERATING_MODE_TYPE::NORMAL){
        *RETURN_CODE = RETURN_CODE_TYPE::INVALID_MODE;
        return;
    }
    for (auto& partitionMutex : partitionMutexes) {
        if (*currentPartition->partitionName.x == partitionMutex.partitionName) {
        //TODO: add if case for operation mode
        if(MAX_NUMBER_OF_MUTEXES == getMutexAmount()){
            *RETURN_CODE = RETURN_CODE_TYPE::INVALID_CONFIG;
            return;
        }
        else if (MUTEX_PRIORITY > 3)// TODO: find out when Mutex is out of range
        {
            *RETURN_CODE = RETURN_CODE_TYPE::INVALID_PARAM;
            return;
        }
        for (auto& mutex : partitionMutex.mutexes) {
            if (*mutex.mutexName.x == *MUTEX_NAME.x) {
                *RETURN_CODE = RETURN_CODE_TYPE::NO_ACTION;
                return;
            }
        }
        
        *MUTEX_ID = partitionMutex.mutexes.size() + rand();

        // Create Mutex
        partitionMutex.mutexes.push_back({MUTEX_NAME, *MUTEX_ID, QUEUING_DISCIPLINE, 
                                        {{}, MUTEX_STATE_TYPE::AVAILABLE, MUTEX_PRIORITY, 0, {} }});
        

        *RETURN_CODE = RETURN_CODE_TYPE::NO_ERROR;
        return;
        }
    }

    *RETURN_CODE = RETURN_CODE_TYPE::NOT_AVAILABLE;
}

/**
 * @brief Acquires a mutex for a process
 *
 * @param MUTEX_ID
 * @param TIME_OUT
 * @param RETURN_CODE
 */
void ApexMutex::ACQUIRE_MUTEX(
    /*in */ MUTEX_ID_TYPE MUTEX_ID,
    /*in */ SYSTEM_TIME_TYPE TIME_OUT,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE){

        auto* currentPartition = CyclicExecutiveSchedule::getCurrentPartition();
        
        name_t currentPartitionName;
        currentPartitionName.x = currentPartition->partitionName;
        ProcessSchedule process(currentPartitionName);
        auto currentProcess = process.getCurrentProcess();

        for (auto& partitionMutex : partitionMutexes) {
            for (auto& mutex : partitionMutex.mutexes) {
                if (mutex.mutexId == MUTEX_ID) {
                    if (mutex.mutex.MUTEX_STATE == MUTEX_STATE_TYPE::AVAILABLE){

                        mutex.mutex.MUTEX_STATE = MUTEX_STATE_TYPE::OWNED;
                        mutex.mutex.MUTEX_OWNER = currentProcess->process->ATTRIBUTES.ID;
                        mutex.mutex.LOCK_COUNT++;
                        currentProcess->process->CURRENT_PRIORITY = mutex.mutex.MUTEX_PRIORITY;
                        currentProcess->process->PROCESS_STATE = PROCESS_STATE_TYPE::READY;

                        *RETURN_CODE = RETURN_CODE_TYPE::NO_ERROR;
                        return;
                    }
                    else if(mutex.mutex.MUTEX_STATE == MUTEX_STATE_TYPE::OWNED && 
                            mutex.mutex.MUTEX_OWNER == currentProcess->process->ATTRIBUTES.ID){
                        if(mutex.mutex.LOCK_COUNT == MAX_LOCK_LEVEL){
                            *RETURN_CODE = RETURN_CODE_TYPE::INVALID_CONFIG;
                            return;
                        }
                        else{
                            mutex.mutex.LOCK_COUNT++;
                            *RETURN_CODE = RETURN_CODE_TYPE::NO_ERROR;
                            return;
                        }
                    }
                    else if (TIME_OUT == 0){
                        *RETURN_CODE = RETURN_CODE_TYPE::NOT_AVAILABLE;
                        return;
                    }
                    else if (TIME_OUT < 0){
                        currentProcess->process->PROCESS_STATE = PROCESS_STATE_TYPE::WAITING;
                        *RETURN_CODE = RETURN_CODE_TYPE::NO_ERROR;
                        return;
                    }
                    else{
                        currentProcess->process->PROCESS_STATE = PROCESS_STATE_TYPE::WAITING;
                        mutex.waitingProcesses.push(currentProcess->process->ATTRIBUTES.ID);
                    }
                }
            }
        }
    *RETURN_CODE = RETURN_CODE_TYPE::INVALID_PARAM;
    return;
}

/**
 * @brief Releases a mutex from a process
 *
 * @param MUTEX_ID
 * @param RETURN_CODE
 */
void ApexMutex::RELEASE_MUTEX(
    /*in */ MUTEX_ID_TYPE MUTEX_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE){
    
    auto* currentPartition = CyclicExecutiveSchedule::getCurrentPartition();

    name_t currentPartitionName;
    currentPartitionName.x = currentPartition->partitionName;
    ProcessSchedule process(currentPartitionName);
    auto currentProcess = process.getCurrentProcess();

    for (auto& partitionMutex : partitionMutexes) {
        for (auto& mutex : partitionMutex.mutexes) {
            if (mutex.mutexId == MUTEX_ID) {
                if(mutex.mutexId == PREEMPTION_LOCK_MUTEX){
                    *RETURN_CODE = RETURN_CODE_TYPE::INVALID_PARAM;
                    return;
                }
                else{
                    if(currentProcess->process->ATTRIBUTES.ID != mutex.mutex.MUTEX_OWNER){
                        *RETURN_CODE = RETURN_CODE_TYPE::INVALID_MODE;
                        return;         
                    }
                    else{
                        mutex.mutex.LOCK_COUNT--;
                        if(mutex.mutex.LOCK_COUNT == 0){
                            mutex.mutex.MUTEX_STATE = MUTEX_STATE_TYPE::AVAILABLE;
                            mutex.mutex.MUTEX_OWNER = NULL_PROCESS_ID;
                            currentProcess->process->PROCESS_STATE = PROCESS_STATE_TYPE::READY;
                            if(mutex.waitingProcesses.size() != 0){
                                auto blockedProcesses = process.getBlockedQueue();
                                for(auto blockedProcess : blockedProcesses){
                                    if(blockedProcess->process->ATTRIBUTES.ID == mutex.waitingProcesses.front()){
                                        //todo if (the removed process is waiting on the mutex with a time-out)
                                        mutex.mutex.MUTEX_STATE = MUTEX_STATE_TYPE::OWNED;
                                        mutex.mutex.LOCK_COUNT++;
                                        mutex.mutex.MUTEX_OWNER = blockedProcess->process->ATTRIBUTES.ID;
                                    }
                                }
                                auto readyProcesses = process.getReadyQueue();
                                for(auto readyProcess : readyProcesses){
                                    if(readyProcess->process->ATTRIBUTES.ID == mutex.waitingProcesses.front()){
                                        //todo if (the removed process is waiting on the mutex with a time-out)
                                        mutex.mutex.MUTEX_STATE = MUTEX_STATE_TYPE::OWNED;
                                        mutex.mutex.LOCK_COUNT++;
                                        mutex.mutex.MUTEX_OWNER = readyProcess->process->ATTRIBUTES.ID;
                                    }
                                }
                                mutex.waitingProcesses.pop();
                            }
                        }
                        *RETURN_CODE = RETURN_CODE_TYPE::NO_ERROR;
                    }
                }
            }
        }
    }
    *RETURN_CODE = RETURN_CODE_TYPE::INVALID_PARAM;
    return;
}

/**
 * @brief Resets a mutex from a process
 *
 * @param MUTEX_ID
 * @param PROCESS_ID
 * @param RETURN_CODE
 */
void ApexMutex::RESET_MUTEX(
    /*in */ MUTEX_ID_TYPE MUTEX_ID,
    /*in */ PROCESS_ID_TYPE PROCESS_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE){

    auto* currentPartition = CyclicExecutiveSchedule::getCurrentPartition();

    name_t currentPartitionName;
    currentPartitionName.x = currentPartition->partitionName;
    ProcessSchedule process(currentPartitionName);

    for (auto& partitionMutex : partitionMutexes) {
        for (auto& mutex : partitionMutex.mutexes) {
            if(mutex.mutexId == MUTEX_ID){
                if(mutex.mutexId == PREEMPTION_LOCK_MUTEX){
                    *RETURN_CODE = RETURN_CODE_TYPE::INVALID_PARAM;
                    return;
                }
                else {
                    if(mutex.mutex.MUTEX_OWNER != PROCESS_ID){
                        *RETURN_CODE = RETURN_CODE_TYPE::INVALID_MODE;
                    }
                    else{
                        mutex.mutex.LOCK_COUNT = 0;
                        mutex.mutex.MUTEX_STATE = MUTEX_STATE_TYPE::AVAILABLE;
                        mutex.mutex.MUTEX_OWNER = NULL_PROCESS_ID;
                        if(mutex.waitingProcesses.size() != 0){
                                auto blockedProcesses = process.getBlockedQueue();
                                for(auto blockedProcess : blockedProcesses){
                                    if(blockedProcess->process->ATTRIBUTES.ID == mutex.waitingProcesses.front()){
                                        //todo if (the removed process is waiting on the mutex with a time-out)
                                        mutex.mutex.MUTEX_STATE = MUTEX_STATE_TYPE::OWNED;
                                        mutex.mutex.LOCK_COUNT++;
                                        mutex.mutex.MUTEX_OWNER = blockedProcess->process->ATTRIBUTES.ID;
                                    }
                                }
                                auto readyProcesses = process.getReadyQueue();
                                for(auto readyProcess : readyProcesses){
                                    if(readyProcess->process->ATTRIBUTES.ID == mutex.waitingProcesses.front()){
                                        //todo if (the removed process is waiting on the mutex with a time-out)
                                        mutex.mutex.MUTEX_STATE = MUTEX_STATE_TYPE::OWNED;
                                        mutex.mutex.LOCK_COUNT++;
                                        mutex.mutex.MUTEX_OWNER = readyProcess->process->ATTRIBUTES.ID;
                                    }
                                }
                                mutex.waitingProcesses.pop();
                            }
                    }
                }
            }
        }
    }
    *RETURN_CODE = RETURN_CODE_TYPE::INVALID_PARAM;
    return;
}

/**
 * @brief return mutexes ID
 *
 * @param MUTEX_NAME
 * @param MUTEX_ID
 * @param RETURN_CODE
 */
void ApexMutex::GET_MUTEX_ID(
    /*in */ MUTEX_NAME_TYPE MUTEX_NAME,
    /*out */ MUTEX_ID_TYPE* MUTEX_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE){
        for (auto& partitionMutex : partitionMutexes){
            for (auto mutex : partitionMutex.mutexes){
                if(*MUTEX_NAME.x == *mutex.mutexName.x){
                    *MUTEX_ID = mutex.mutexId;
                    *RETURN_CODE = RETURN_CODE_TYPE::NO_ERROR;
                    return;
                }
            }
        }
    *RETURN_CODE = RETURN_CODE_TYPE::INVALID_CONFIG;
    return;
}

/**
 * @brief returns mutex status
 *
 * @param MUTEX_ID
 * @param MUTEX_STATUS
 * @param RETURN_CODE
 */
void ApexMutex::GET_MUTEX_STATUS(
    /*in */ MUTEX_ID_TYPE MUTEX_ID,
    /*out*/ MUTEX_STATUS_TYPE MUTEX_STATUS,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE){
    for (auto& partitionMutex : partitionMutexes){
        for (auto mutex : partitionMutex.mutexes){
            if(mutex.mutexId = MUTEX_ID)
            {
                MUTEX_STATUS = mutex.mutex;
                *RETURN_CODE = RETURN_CODE_TYPE::NO_ERROR;
                return;
            }
        }
    }
    *RETURN_CODE = RETURN_CODE_TYPE::INVALID_PARAM;
    return;
}

void ApexMutex::initialiseMutex()
{
    auto& module = ArincModule::generatedArincModule;

    for (auto& partition : module.partitions) {
        partitionMutexes.push_back({*partition.getPartitionName().x.x, {}});
    }
}