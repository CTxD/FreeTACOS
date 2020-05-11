#include "partitionscheduling.hpp"
#include <arch.h>
#include <arinc_module.hpp>
#include <circle/time.h>
#include <core_schedule.hpp>
#include <defines.hpp>
#include <generated_partition_schedule.hpp>
#include <partition.hpp>
#include <partition_schedule.hpp>

RunningPartition* CyclicExecutiveSchedule::currentPartition = nullptr;

void CyclicExecutiveSchedule::partitionHandler()
{
    for (int i = 0; i < coreSize; i++) {
        if (runningPartition[0].endTime == 0 ||
            CTimer::Get()->GetClockTicks() >= runningPartition[i].endTime) {
            getNextPartition(runningPartition, coreSize);
        }
    }
}
/**
 * DESCRIPTION: Gets the next partition to run
 * RETURN: RunningPartition*
 */
RunningPartition* CyclicExecutiveSchedule::getNextPartition(RunningPartition* runningPartition,
                                                            int size)
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
                runningPartition[i].endTime = currentTime + partitions[0].getDuration();
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
                        currentTime + partitions[0].getDuration();
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
                        currentTime + partitions[nextIndex].getDuration();
                    runningPartition[i].index = nextIndex;
                }
            }
        }
    }
    // prints runningPartition to the screen
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
    return runningPartition;
}
/**
 * DESCRIPTION: Starts and runs the Cyclic Executive schedule
 */
void CyclicExecutiveSchedule::startPartitionScheduler()
{
    // prints debug info to the screen
#if KERNEL_DEBUG()
    CLogger::Get()->Write("FreeTACOS", LogNotice, "Starting partition schedule");
#endif
    // initialize RunningPartition array
#if KERNEL_PROCESSER(IS_MULTICORE)
    coreSize = 4;
    running_partition[0] = {"", 0, 0, 0, 0, "", 0, 0, 0, 0,
                            "", 0, 0, 0, 0, "", 0, 0, 0, 0};
#elif KERNEL_PROCESSER(IS_SINGLECORE)
    coreSize = 1;
    runningPartition[0] = {"", 0, 0, 0, 0};
#else
    assert(0); // abort
#endif
    for (int i = 0; i < coreSize; i++) {
        if (runningPartition[0].endTime == 0 ||
            CTimer::Get()->GetClockTicks() >= runningPartition[i].endTime) {
            getNextPartition(runningPartition, coreSize);
            // Run the next partition's process
            name_t partitionName = {*runningPartition[0].partitionName.x};
            auto* processSchedule = ProcessSchedule::getProcessScheduleByName(partitionName);
            processSchedule->startScheduler();
            break;
        }
    }
}

void CyclicExecutiveSchedule::initPartitionScheduler()
{
    // prints debug info to the screen
#if KERNEL_DEBUG()
    CLogger::Get()->Write("FreeTACOS", LogNotice, "Init partition schedule");
#endif
    // initialize RunningPartition array
#if KERNEL_PROCESSER(IS_MULTICORE)
    coreSize = 4;
    running_partition[0] = {"", 0, 0, 0, 0, "", 0, 0, 0, 0,
                            "", 0, 0, 0, 0, "", 0, 0, 0, 0};
#elif KERNEL_PROCESSER(IS_SINGLECORE)
    coreSize = 1;
    runningPartition[0] = {"", 0, 0, 0, 0};
#else
    assert(0); // abort
#endif
}

/**
 * DESCRIPTION: Gets the currently running partition
 * RETURN: RunningPartition*
 */
RunningPartition* CyclicExecutiveSchedule::getCurrentPartition()
{
    return currentPartition;
}