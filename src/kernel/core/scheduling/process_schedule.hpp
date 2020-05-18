#ifndef _TACOS_PROCESS_SCHEDULE
#define _TACOS_PROCESS_SCHEDULE

#include <apex_kernel.hpp>
#include <apex_partition.hpp>
#include <apex_process.hpp>
#include <apex_types.hpp>

#include <partitionscheduling.hpp>

#include <vector>

#include <circle/timer.h>

struct ProcessScheduleInfo {
    SYSTEM_TIME_TYPE period;
    SYSTEM_TIME_TYPE startTime;
    SYSTEM_TIME_TYPE endTime;
    PROCESS_STATUS_TYPE* process;
};

class ProcessSchedule {
private:
    name_t scheduleName;
    std::vector<ProcessScheduleInfo*> readyQueue;
    std::vector<ProcessScheduleInfo*> blockedQueue;

    ProcessScheduleInfo* runningProcess;
    ProcessScheduleInfo* terminatedProcess;

    void iterate();
    void reReadyProcesses();
    void runNextProcess();

    ProcessScheduleInfo* getNextProcess(PROCESS_ID_TYPE& procId);

public:
    void startScheduler();

    ProcessSchedule(name_t partitionType);

    void addProcess(PROCESS_STATUS_TYPE* process);
    name_t* getProcessScheduleName();

    static void initialiseSchedules();
    static std::vector<ProcessSchedule*> scheduleList[MAX_NUMBER_OF_PARTITIONS];
    static bool isInitialised;
    static ProcessSchedule* getProcessScheduleByName(name_t& scheduleName);

    ProcessScheduleInfo* getCurrentProcess();
    std::vector<ProcessScheduleInfo*> getReadyQueue();
    std::vector<ProcessScheduleInfo*> getBlockedQueue();
};

#endif