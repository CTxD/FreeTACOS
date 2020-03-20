#ifndef _TACOS_PROCESS_SCHEDULE
#define _TACOS_PROCESS_SCHEDULE

#include <apex_kernel.hpp>

#include <apex_process.hpp>
#include <apex_types.hpp>
#include <vector>

class ProcessSchedule {
private:
    NAME_TYPE partitionName;
    std::vector<PROCESS_STATUS_TYPE*> readyQueue;
    std::vector<PROCESS_STATUS_TYPE*> blockedQueue;

    PROCESS_STATUS_TYPE* runningProcess;
    PROCESS_STATUS_TYPE* terminatedProcess;

    void iterate();
    bool checkIteration();

    PROCESS_STATUS_TYPE* getNextProcess();

    static bool isInitalised;

public:
    ProcessSchedule(NAME_TYPE partitionType);

    void addProcess(PROCESS_STATUS_TYPE* process);
    void interruptHandler();

    static void initialiseSchedules();
};

#endif