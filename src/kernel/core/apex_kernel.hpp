#ifndef _FREETACOS_APEX_KERNEL
#define _FREETACOS_APEX_KERNEL

#include <apex_process.h>
#include <apex_types.h>

#include <task.hpp>

const u32 MAX_PROCESSES = MAX_NUMBER_OF_PROCESSES;

static u32 numProcesses = 0;
static Task* processPool[MAX_PROCESSES]{};
static RETURN_CODE_TYPE addToProcessList(Task* process)
{
    // Check if we exceed max number of processes
    if (numProcesses == MAX_PROCESSES) {
        // Function call not_available
        return RETURN_CODE_TYPE::NOT_AVAILABLE;
    }

    processPool[numProcesses] = process;
    numProcesses++;

    return RETURN_CODE_TYPE::NO_ERROR;
}

#endif