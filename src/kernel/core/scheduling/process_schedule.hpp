#ifndef _TACOS_PROCESS_SCHEDULE
#define _TACOS_PROCESS_SCHEDULE

#include <apex_kernel.hpp>
#include <apex_partition.hpp>
#include <apex_process.hpp>
#include <apex_types.hpp>

#include <vector>

class ProcessSchedule {
private:
    name_t scheduleName;
    std::vector<PROCESS_STATUS_TYPE*> readyQueue;
    std::vector<PROCESS_STATUS_TYPE*> blockedQueue;

    PROCESS_STATUS_TYPE* runningProcess;
    PROCESS_STATUS_TYPE* terminatedProcess;

    void iterate();
    bool checkIteration();

    PROCESS_STATUS_TYPE* getNextProcess();

public:
    ProcessSchedule(name_t partitionType);

    void addProcess(PROCESS_STATUS_TYPE* process);
    void interruptHandler();
    name_t* getProcessScheduleName();

    static void initialiseSchedules();
    static std::vector<ProcessSchedule*> scheduleList[MAX_NUMBER_OF_PARTITIONS];
    static bool isInitialised;
    static ProcessSchedule* getProcessScheduleByName(name_t& scheduleName);
};

#endif