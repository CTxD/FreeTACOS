#ifndef __APEX_KERNEL__
#define __APEX_KERNEL__

#include <apex_process.hpp>
#include <apex_types.hpp>

#include <task.hpp>

const u32 MAX_PROCESSES = MAX_NUMBER_OF_PROCESSES;

class ApexKernel {
public:
    static u32 numProcesses;
    static Task* processPool[MAX_PROCESSES];
    static RETURN_CODE_TYPE addToProcessList(Task* process);

    static PROCESS_STATUS_TYPE& getProcessById(PROCESS_ID_TYPE id);
    static void getProcessIdByName(PROCESS_NAME_TYPE name, PROCESS_ID_TYPE* returnId);
};

#endif