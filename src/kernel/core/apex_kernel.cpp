/* File containing infrastructure of the APEX interface,
   and more specifically the process-pools, for creating processes,
   using the APEX interface
*/

#include <apex_kernel.hpp>
#include <process_schedule.hpp>

u32 ApexKernel::numProcesses = 0;
Task* ApexKernel::processPool[MAX_PROCESSES]{};
RETURN_CODE_TYPE ApexKernel::addToProcessList(Task* process)
{
    // Check if we exceed max number of processes
    if (numProcesses == MAX_PROCESSES) {
        // Function call not_available
        return RETURN_CODE_TYPE::NOT_AVAILABLE;
    }

    // Add process to schedule
    addToProcessSchedule(process);

    processPool[numProcesses] = process;
    numProcesses++;

    return RETURN_CODE_TYPE::NO_ERROR;
}

void ApexKernel::addToProcessSchedule(Task* process)
{
    // Retrieve the name of the partition
    // TODO: Change the getProcessName to getPartitionName instead.
    auto& partitionNameRef = process->getPartitionNameRef();

    // Get mathing process schedule
    auto* schedule = ProcessSchedule::GetProcessScheduleByName(partitionNameRef);

    // Check whether one was found or not
    assert(schedule != nullptr && "The partition name of process is invalid");

    // Add the process to the schedules ready list
    schedule->AddProcess(&process->getStatus());
}

PROCESS_STATUS_TYPE& ApexKernel::getProcessById(PROCESS_ID_TYPE id)
{
    return processPool[id]->getStatus();
}

void ApexKernel::getProcessIdByName(PROCESS_NAME_TYPE name, PROCESS_ID_TYPE* returnId)
{
    auto doesProcessExist = false;
    for (u32 i = 0; i < numProcesses; i++) {
        auto& currentProcess = processPool[i];

        if (currentProcess->getStatus().ATTRIBUTES.NAME.x == name.x) {
            *returnId = i;
            doesProcessExist = true;
        }
    }

    if (!doesProcessExist) {
        returnId = nullptr;
    }
}
