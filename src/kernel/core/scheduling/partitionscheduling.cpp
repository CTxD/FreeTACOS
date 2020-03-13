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

struct runningPartition {
    NAME_TYPE partitionName;
    APEX_INTEGER startTime;
    APEX_INTEGER endTime;
    int index;
    int partitionAmount;
};

runningPartition* getNextPartition(runningPartition* running_partition, int size)
{
    // Get first partitions
    if (running_partition[0].endTime == 0) {
        auto currentTime = CTimer::Get()->GetClockTicks();
        for (int i = 0; i < size; i++) {
            auto partitions = coreSchedule.getPartitions(i);
            auto amountOfPartitions = coreSchedule.getPartitions(i).size();
            running_partition[i].partitionAmount = amountOfPartitions;
            // If the core array is not empty
            if (amountOfPartitions > 0) {
                running_partition[i].partitionName = partitions[0].getPartitionName();
                running_partition[i].startTime = currentTime + partitions[0].getOffset();
                running_partition[i].endTime =
                    currentTime + partitions[0].getPeriodDuration();
                running_partition[i].index = 0;
            }
        }
    }
    else {
        // After the first partitions are retrieved
        auto currentTime = CTimer::Get()->GetClockTicks();
        for (int i = 0; i < size; i++) {
            auto partitions = coreSchedule.getPartitions(i);
            // If the a partition has past it's duration
            if (currentTime >= running_partition[i].endTime) {
                running_partition[i].index += 1;
                // If it is the last partition in the core array (then gets the first partition of the core array again)
                if (running_partition[i].index == running_partition[i].partitionAmount) {
                    running_partition[i].partitionName = partitions[0].getPartitionName();
                    running_partition[i].startTime =
                        currentTime + partitions[0].getOffset();
                    running_partition[i].endTime =
                        currentTime + partitions[0].getPeriodDuration();
                    running_partition[i].index = 0;
                }
                else {
                    // If it not the last partition in the core array
                    int nextIndex = running_partition[i].index;
                    running_partition[i].partitionName =
                        partitions[nextIndex].getPartitionName();
                    running_partition[i].startTime =
                        currentTime + partitions[nextIndex].getOffset();
                    running_partition[i].endTime =
                        currentTime + partitions[nextIndex].getPeriodDuration();
                    running_partition[i].index = nextIndex;
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
                              running_partition[i].partitionName.x[0]);
        CLogger::Get()->Write("FreeTACOS", LogNotice,
                              "partition start time = %d", running_partition[i].startTime);
        CLogger::Get()->Write("FreeTACOS", LogNotice, "partition end time = %d",
                              running_partition[i].endTime);
        CLogger::Get()->Write("FreeTACOS", LogNotice,
                              "-----------------------------");
    }
#endif

    // TODO: preemption

    return running_partition;
}

void partitionScheduler()
{
#if KERNEL_PROCESSER(IS_MULTICORE)
    int size = 4;
    runningPartition running_partition[size] = {"", 0, 0, 0, 0, "", 0, 0, 0, 0,
                                                "", 0, 0, 0, 0, "", 0, 0, 0, 0};
#elif KERNEL_PROCESSER(IS_SINGLECORE)
    int size = 1;
    runningPartition running_partition[size] = {"", 0, 0, 0, 0};
#else
    assert(0); // abort
#endif

#if KERNEL_DEBUG()
    CLogger::Get()->Write("FreeTACOS", LogNotice, "Starting partition schedule");
#endif
    getNextPartition(running_partition, size);
    while (1) {
        for (int i = 0; i < size; i++) {
            if (CTimer::Get()->GetClockTicks() >= running_partition[i].endTime) {
                getNextPartition(running_partition, size);
                break;
            }
        }
        // TODO: call process scheduler her
    }
}