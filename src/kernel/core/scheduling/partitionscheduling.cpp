#include "partitionscheduling.hpp"
#include <arch.h>
#include <arinc_module.hpp>
#include <circle/time.h>
#include <core_schedule.hpp>
#include <defines.hpp>
#include <generated_arinc_module.hpp>
#include <generated_partition_schedule.hpp>
#include <partition.hpp>
#include <partition_schedule.hpp>

struct RunningPartition {
    NAME_TYPE partitionName;
    APEX_INTEGER startTime;
    APEX_INTEGER endTime;
    int index;
    int partitionAmount;
};

RunningPartition* getNextPartition(RunningPartition* runningPartition, int size)
{
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

    return runningPartition;
}

void partitionScheduler()
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
    getNextPartition(runningPartition, size);
    while (1) {
        for (int i = 0; i < size; i++) {
            if (CTimer::Get()->GetClockTicks() >= runningPartition[i].endTime) {
                getNextPartition(runningPartition, size);
                break;
            }
        }
        // TODO: call process scheduler her
    }
}