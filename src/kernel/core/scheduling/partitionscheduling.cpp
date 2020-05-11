#include "partitionscheduling.hpp"
#include <arch.h>
#include <arinc_module.hpp>
#include <circle/time.h>
#include <core_schedule.hpp>
#include <defines.hpp>
#include <generated_partition_schedule.hpp>
#include <partition.hpp>
#include <partition_schedule.hpp>
#include <apex_mutex.hpp>
#include <apex_types.hpp>

RunningPartition* CyclicExecutiveSchedule::currentPartition = nullptr;

RunningPartition* CyclicExecutiveSchedule::getNextPartition(RunningPartition* runningPartition,
                                                            int size)
{
    MUTEX_ID_TYPE mutexId;
    RETURN_CODE_TYPE mutexCode;
    MUTEX_STATUS_TYPE mutexStatus;
    // Get first partitions
    if (runningPartition[0].endTime == 0) {
        auto currentTime = CTimer::Get()->GetClockTicks();
        for (int i = 0; i < size; i++) {
            auto partitions = coreSchedule.getPartitions(i);
            auto amountOfPartitions = coreSchedule.getPartitions(i).size();
            runningPartition[i].partitionAmount = amountOfPartitions;
            // If the core array is not empty
            if (amountOfPartitions > 0) {
                runningPartition[i].partitionName = partitions[0].getPartitionName();
                runningPartition[i].startTime = currentTime + partitions[0].getOffset();
                runningPartition[i].endTime =
                    currentTime + partitions[0].getPeriodDuration();
                runningPartition[i].index = 0;
                runningPartition[i].operatingMode = OPERATING_MODE_TYPE::COLD_START;
            }
        }
    }
    else {
        // After the first partitions are retrieved
        auto currentTime = CTimer::Get()->GetClockTicks();
        for (int i = 0; i < size; i++) {
            auto partitions = coreSchedule.getPartitions(i);
            // If the a partition has past it's duration
            if (currentTime >= runningPartition[i].endTime) {
                runningPartition[i].index += 1;
                // If it is the last partition in the core array (then gets the first partition of the core array again)
                if (runningPartition[i].index == runningPartition[i].partitionAmount) {
                    runningPartition[i].partitionName = partitions[0].getPartitionName();
                    runningPartition[i].startTime =
                        currentTime + partitions[0].getOffset();
                    runningPartition[i].endTime =
                        currentTime + partitions[0].getPeriodDuration();
                    runningPartition[i].index = 0;
                }
                else {
                    // If it not the last partition in the core array
                    int nextIndex = runningPartition[i].index;
                    runningPartition[i].partitionName =
                        partitions[nextIndex].getPartitionName();
                    runningPartition[i].startTime =
                        currentTime + partitions[nextIndex].getOffset();
                    runningPartition[i].endTime =
                        currentTime + partitions[nextIndex].getPeriodDuration();
                    runningPartition[i].index = nextIndex;
                }
            }
        }
    }

#if KERNEL_DEBUG()
    for (int i = 0; i < size; i++) {
        CLogger::Get()->Write("FreeTACOS", LogNotice,
                              "---------- CORE %d ----------", i);
        CLogger::Get()->Write("FreeTACOS", LogNotice,
                              "----- Running partition -----");
        CLogger::Get()->Write("FreeTACOS", LogNotice, "partition name = %s",
                              runningPartition[i].partitionName.x[0]);
        CLogger::Get()->Write("FreeTACOS", LogNotice,
                              "partition start time = %d", runningPartition[i].startTime);
        CLogger::Get()->Write("FreeTACOS", LogNotice, "partition end time = %d",
                              runningPartition[i].endTime);
        CLogger::Get()->Write("FreeTACOS", LogNotice,
                              "-----------------------------");
    }
#endif

    // TODO: preemption
    // Set currentPartition
    CyclicExecutiveSchedule::currentPartition = runningPartition;
    
    ApexMutex::CREATE_MUTEX({"TestMutex"},1,QUEUING_DISCIPLINE_TYPE::FIFO,mutexId,&mutexCode);
    if (mutexCode == NO_ERROR) {
        CLogger::Get()->Write("Tester", LogNotice, "Mutex created with id: %i returnCode: %d", mutexId, mutexCode);
    }
    else {
        CLogger::Get()->Write("Tester", LogNotice, "Error creating mutex %i returnCode: %d ", mutexId, mutexCode);
    }

    ApexMutex::GET_MUTEX_STATUS(mutexId, mutexStatus, &mutexCode);
    if (mutexCode == NO_ERROR) {
        CLogger::Get()->Write("Tester", LogNotice, "Mutex Status");
    }
    else {
        CLogger::Get()->Write("Tester", LogNotice, "Error getting mutex status %i returnCode: %d", mutexId, mutexCode);
    }
    return runningPartition;
}

void CyclicExecutiveSchedule::partitionScheduler()
{
#if KERNEL_PROCESSER(IS_MULTICORE)
    int size = 4;
    RunningPartition running_partition[size] = {"", 0, 0, 0, 0, "", 0, 0, 0, 0,
                                                "", 0, 0, 0, 0, "", 0, 0, 0, 0};
#elif KERNEL_PROCESSER(IS_SINGLECORE)
    int size = 1;
    RunningPartition runningPartition[size] = {"", 0, 0, 0, 0};
#else
    assert(0); // abort
#endif

#if KERNEL_DEBUG()
    CLogger::Get()->Write("FreeTACOS", LogNotice, "Starting partition schedule");
#endif

    while (1) {
        for (int i = 0; i < size; i++) {
            if (runningPartition[0].endTime == 0 ||
                CTimer::Get()->GetClockTicks() >= runningPartition[i].endTime) {
                getNextPartition(runningPartition, size);

                // Run the next partition's process
                name_t partitionName = {*runningPartition[0].partitionName.x};
                auto* processSchedule =
                    ProcessSchedule::getProcessScheduleByName(partitionName);

                processSchedule->startScheduler();

                break;
            }
        }
    }
}

RunningPartition* CyclicExecutiveSchedule::getCurrentPartition()
{
    return currentPartition;
}