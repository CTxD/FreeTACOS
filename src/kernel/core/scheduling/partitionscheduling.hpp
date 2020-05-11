#ifndef __PARTITION_SCHEDULING__
#define __PARTITION_SCHEDULING__

#include <apex_types.hpp>
#include <process_schedule.hpp>

struct RunningPartition {
    NAME_TYPE partitionName;
    APEX_INTEGER startTime;
    APEX_INTEGER endTime;
    int index;
    int partitionAmount;
    OPERATING_MODE_TYPE operatingMode;
};

class CyclicExecutiveSchedule {
private:
    RunningPartition* getNextPartition(RunningPartition* runningPartition, int size);

    static RunningPartition* currentPartition;

public:
    void partitionScheduler();

    static RunningPartition* getCurrentPartition();
};

#endif