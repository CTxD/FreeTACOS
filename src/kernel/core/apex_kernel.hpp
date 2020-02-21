/* File containing infrastructure of the APEX interface,
   and more specifically the process-pools, for creating processes,
   using the APEX interface
*/

#include <apex_process.h>
#include <apex_types.h>

#include <test_app.h>

u64 numProcesses = 0;

static Task* processPool[MAX_NUMBER_OF_PROCESSES]{};
static void addToProcessList(Task* process)
{
    // Check if we exceed max number of processes
    if (numProcesses == MAX_NUMBER_OF_PROCESSES) {
        // TODO: FIX: Health Monitor, rescue this!
    }

    processPool[numProcesses] = process;
    numProcesses++;
}