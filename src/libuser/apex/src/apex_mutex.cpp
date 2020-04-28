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
        partitionMutex.mutexes.push_back({MUTEX_NAME, QUEUING_DISCIPLINE, 
                                        {{}, MUTEX_STATE_TYPE::AVAILABLE, MUTEX_PRIORITY, 0, {} }});

        MUTEX_ID = partitionMutex.mutexes.size() - 1;
        *RETURN_CODE = NO_ERROR;
        return;
        }
    }

    *RETURN_CODE = NOT_AVAILABLE;
    MUTEX_ID = -1;
}

