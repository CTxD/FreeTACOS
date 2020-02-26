#include "partitionscheduling.hpp"
#include <arch.h>
#include <arinc_module.hpp>
#include <circle/time.h>
#include <core_schedule.hpp>
#include <generated_arinc_module.hpp>
#include <generated_core_schedule.hpp>
#include <partition.hpp>
#include <partition_schedule.hpp>

struct runningPartition {
    name_t partitionName;
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

    return running_partition;
}

void partitionScheduler()
{
    int size = 4;
    runningPartition running_partition[size] = {"", 0, 0, 0, 0, "", 0, 0, 0, 0,
                                                "", 0, 0, 0, 0, "", 0, 0, 0, 0};
    getNextPartition(running_partition, size);
    while (1) {
        for (int i = 0; i < size; i++) {
            if (CTimer::Get()->GetClockTicks() >= running_partition[i].endTime) {
                getNextPartition(running_partition, size);
                break;
            }
        }
    }
}