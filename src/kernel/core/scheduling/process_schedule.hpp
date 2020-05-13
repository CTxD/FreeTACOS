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

    void ReReadyProcesses();
    void RunNextProcess();

    ProcessScheduleInfo* GetNextProcess(PROCESS_ID_TYPE& procId);

public:
    void StartScheduler();
    void Iterate();

    ProcessSchedule(name_t partitionType);

    void AddProcess(PROCESS_STATUS_TYPE* process);
    name_t* GetProcessScheduleName();

    static void InitialiseSchedules();
    static ProcessSchedule* GetProcessScheduleByName(name_t& scheduleName);
    static std::vector<ProcessSchedule*> scheduleList[MAX_NUMBER_OF_PARTITIONS];
    static bool isInitialised;
};

#endif