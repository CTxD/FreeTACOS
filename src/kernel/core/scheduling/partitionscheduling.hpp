#ifndef __PARTITION_SCHEDULING__
#define __PARTITION_SCHEDULING__
#include <apex_types.hpp>
#include <defines.hpp>
#include <process_schedule.hpp>

struct RunningPartition {
    NAME_TYPE partitionName;
    APEX_INTEGER startTime;
    APEX_INTEGER endTime;
    int index;
    int partitionAmount;
};
class CyclicExecutiveSchedule {
private:
    RunningPartition* getNextPartition(RunningPartition* runningPartition, int size);
    static RunningPartition* currentPartition;
    int coreSize;
#if KERNEL_PROCESSER(IS_MULTICORE)
    RunningPartition runningPartition[4];
#elif KERNEL_PROCESSER(IS_SINGLECORE)
    RunningPartition runningPartition[1];
#else
    assert(0); // abort
#endif

public:
    void partitionHandler();
    void startPartitionScheduler();
    void initPartitionScheduler();
    static RunningPartition* getCurrentPartition();
};
#endif