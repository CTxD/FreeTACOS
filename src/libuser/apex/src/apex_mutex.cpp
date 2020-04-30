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

void ApexMutex::CREATE_MUTEX(
    /*in */ MUTEX_NAME_TYPE MUTEX_NAME,
    /*in */ PRIORITY_TYPE MUTEX_PRIORITY,
    /*in */ QUEUING_DISCIPLINE_TYPE QUEUING_DISCIPLINE,
    /*out*/ MUTEX_ID_TYPE MUTEX_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE){

    auto* currentPartition = CyclicExecutiveSchedule::getCurrentPartition();

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

void ApexMutex::ACQUIRE_MUTEX(
    /*in */ MUTEX_ID_TYPE MUTEX_ID,
    /*in */ SYSTEM_TIME_TYPE TIME_OUT,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE){

    }

void ApexMutex::RELEASE_MUTEX(
    /*in */ MUTEX_ID_TYPE MUTEX_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE){

}

void ApexMutex::RESET_MUTEX(
    /*in */ MUTEX_ID_TYPE MUTEX_ID,
    /*in */ PROCESS_ID_TYPE PROCESS_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE){

}

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