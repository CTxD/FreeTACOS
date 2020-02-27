/* File containing infrastructure of the APEX interface,
   and more specifically the process-pools, for creating processes,
   using the APEX interface
*/
#include <apex_kernel.hpp>

u32 ApexKernel::numProcesses = 0;
Task* ApexKernel::processPool[MAX_PROCESSES]{};
RETURN_CODE_TYPE ApexKernel::addToProcessList(Task* process)
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