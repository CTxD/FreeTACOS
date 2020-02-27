#include <apex_process.h>
#include <apex_types.h>

#include <task.hpp>

const u32 MAX_PROCESSES = MAX_NUMBER_OF_PROCESSES;

class ApexKernel {
public:
    static u32 numProcesses;
    static Task* processPool[MAX_PROCESSES];
    static RETURN_CODE_TYPE addToProcessList(Task* process);
};