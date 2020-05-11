#include <apex_mutex.hpp>
#include <apex_types.hpp>
#include <partitionscheduling.hpp>

#include <vector>

std::vector<PartitionMutex> ApexMutex::partitionMutexes{};

int ApexMutex::getMutexAmount(){
    int numberOfMutexes;
    for (auto& partitionMutex : partitionMutexes){
        for (auto& mutex : partitionMutex.mutexes){
            numberOfMutexes++;
        }
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
    /*out*/ MUTEX_ID_TYPE MUTEX_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE){

    auto* currentPartition = CyclicExecutiveSchedule::getCurrentPartition();

    if(currentPartition->operatingMode == OPERATING_MODE_TYPE::NORMAL){
        *RETURN_CODE = INVALID_MODE;
        return;
    }

    for (auto& partitionMutex : partitionMutexes) {
        if (*currentPartition->partitionName.x == partitionMutex.partitionName) {
        //TODO: add if case for operation mode
        if(MAX_NUMBER_OF_MUTEXES == getMutexAmount()){
            *RETURN_CODE = INVALID_CONFIG;
            return;
        }
        else if ((MUTEX_PRIORITY > 3) || 
                (QUEUING_DISCIPLINE != QUEUING_DISCIPLINE_TYPE::FIFO || 
                QUEUING_DISCIPLINE_TYPE::PRIORITY)) // TODO: find out when Mutex is out of range
        {
            *RETURN_CODE = INVALID_PARAM;
            return;
        }
        for (auto& mutex : partitionMutex.mutexes) {
            if (*mutex.mutexName.x == *MUTEX_NAME.x) {
                *RETURN_CODE = NO_ACTION;
                return;
            }
        }
        
        // Create Mutex
        MUTEX_ID = partitionMutex.mutexes.size() - 1;
        partitionMutex.mutexes.push_back({MUTEX_NAME, MUTEX_ID, QUEUING_DISCIPLINE, 
                                        {{}, MUTEX_STATE_TYPE::AVAILABLE, MUTEX_PRIORITY, 0, {} }});
        *RETURN_CODE = NO_ERROR;
        return;
        }
    }

    *RETURN_CODE = NOT_AVAILABLE;
    MUTEX_ID = -1;
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
                    if (mutex.mutex.MUTEX_OWNER == MUTEX_STATE_TYPE::AVAILABLE){
                        // todo: set values
                        mutex.mutex.MUTEX_OWNER = MUTEX_STATE_TYPE::OWNED;
                        // todo: get the current process id
                        //currentProcess
                        //mutex.mutex.MUTEX_OWNER = currentProcess->process->ATTRIBUTES;
                        mutex.mutex.LOCK_COUNT++;
                        // todo: retain the current priority of the current process;
                        // raise the current priority of the process to the mutex’s priority,
                        // positioning the process as being in the ready state for the longest
                        // elapsed time at that priority (i.e., other processes at the same priority
                        // will be selected to run after this process);
                        *RETURN_CODE = NO_ERROR;
                        return;
                    }
                }
            }
        }
    *RETURN_CODE = INVALID_PARAM;
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

    for (auto& partitionMutex : partitionMutexes) {
        for (auto& mutex : partitionMutex.mutexes) {
            if (mutex.mutexId == MUTEX_ID) {
            //when (MUTEX_ID is equal to PREEMPTION_LOCK_MUTEX) =>
            // -- no direct access for using the partition’s preemption lock mutex
            // RETURN_CODE := INVALID_PARAM;
            // when (the current process does not own the specified mutex) =>
            // RETURN_CODE := INVALID_MODE;
            mutex.mutex.LOCK_COUNT--;
            mutex.mutex.MUTEX_OWNER = MUTEX_STATE_TYPE::AVAILABLE;
            // restore the current priority of the owning process to its retained
            // current priority, positioning the process as being in the ready
            // state for the longest elapsed time at this priority (i.e., other
            // processes at the same priority will be selected to run after
            // this process);
            }
        }
    }
    *RETURN_CODE = INVALID_PARAM;
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
    for (auto& partitionMutex : partitionMutexes) {
        for (auto& mutex : partitionMutex.mutexes) {
        }
    }
}

/**
 * @brief 
 *
 * @param MUTEX_NAME
 * @param MUTEX_ID
 * @param RETURN_CODE
 */
void ApexMutex::GET_MUTEX_ID(
    /*in */ MUTEX_NAME_TYPE MUTEX_NAME,
    /*in */ MUTEX_ID_TYPE MUTEX_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE){
        for (auto& partitionMutex : partitionMutexes){
            for (auto mutex : partitionMutex.mutexes){
                if(*MUTEX_NAME.x == *mutex.mutexName.x){
                    *RETURN_CODE = NO_ERROR;
                    return;
                }
            }
        }
    *RETURN_CODE = INVALID_CONFIG;
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
                *RETURN_CODE = NO_ERROR;
                return;
            }
        }
    }
    *RETURN_CODE = INVALID_PARAM;
    return;
}