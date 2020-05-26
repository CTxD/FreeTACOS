#include "process.hpp"
#include "apex_kernel.hpp"

#define INVALID_PROCESS_ID (MAX_NUMBER_OF_PROCESSES + 1)

Process::Process(PROCESS_ATTRIBUTE_TYPE& attributes)
{
    // Initialise PROCESS_STATUS
    status.ATTRIBUTES = attributes;
    status.CURRENT_PRIORITY = attributes.BASE_PRIORITY;
    status.DEADLINE_TIME = attributes.TIME_CAPACITY;
    status.PROCESS_STATE = PROCESS_STATE_TYPE::DORMANT;
    id = INVALID_PROCESS_ID;
}

Process::Process(PROCESS_STATUS_TYPE& status) : status(status)
{
    id = INVALID_PROCESS_ID;
}

Process::Process()
{
}

PROCESS_NAME_TYPE& Process::getProcessName()
{
    return this->status.ATTRIBUTES.NAME;
}

PROCESS_STATUS_TYPE& Process::getStatus()
{
    return this->status;
}

void Process::setStatus(PROCESS_STATUS_TYPE& status)
{
    this->status = status;
}

PROCESS_ID_TYPE Process::getId()
{
    return this->id;
}

void Process::setId(PROCESS_ID_TYPE pId)
{
    this->id = pId;
}

/* APEX Functionality Below */
void Process::CREATE_PROCESS(
    /*in */ PROCESS_ATTRIBUTE_TYPE* ATTRIBUTES,
    /*out*/ PROCESS_ID_TYPE* PROCESS_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    // Init new process with attributes (Create the process)
    auto* proc = static_cast<Task*>(ATTRIBUTES->ENTRY_POINT);
    proc->getStatus().ATTRIBUTES = *ATTRIBUTES;

    // Get the process id
    PROCESS_ID_TYPE pId;
    pId = ApexKernel::numProcesses;

    proc->status.ATTRIBUTES.ID = pId;
    // Add the process to the apex_kernel process list
    ApexKernel::addToProcessList(proc);

    // Set id and return
    static_cast<Task*>(ATTRIBUTES->ENTRY_POINT)->setId(pId);

    *PROCESS_ID = pId;
    *RETURN_CODE = NO_ERROR;
}
void Process::SET_PRIORITY(
    /*in */ PROCESS_ID_TYPE PROCESS_ID,
    /*in */ PRIORITY_TYPE PRIORITY,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    auto& process = status;
    if (process.CURRENT_PRIORITY == PRIORITY) {
        // No action, since the prioties are the same
        *RETURN_CODE = NO_ACTION;
        return;
    }

    status.CURRENT_PRIORITY = PRIORITY;
    *RETURN_CODE = NO_ERROR;
}

void Process::SUSPEND_SELF(
    /*in */ SYSTEM_TIME_TYPE TIME_OUT,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    // Do some timing here, and set the mode to suspended, until time has passed.

    // Get own process id
    PROCESS_ID_TYPE myId;
    RETURN_CODE_TYPE myCode;
    GET_MY_ID(&myId, &myCode);

    // Check if i exist
    if (myCode != NO_ERROR) {
        *RETURN_CODE = INVALID_PARAM;
        return;
    }

    // Suspend myself
    RETURN_CODE_TYPE returnCode;
    SUSPEND(myId, &returnCode);

    // Check if SUSPEND was successful
    if (returnCode != NO_ERROR) {
        returnCode = RETURN_CODE_TYPE::NOT_AVAILABLE;
        return;
    }

    // Should be NO_ERROR, if SUSPEND was successful
    *RETURN_CODE = returnCode;
}

void Process::SUSPEND(
    /*in */ PROCESS_ID_TYPE PROCESS_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    auto& process = status;
    if (process.PROCESS_STATE == WAITING) {
        // No action, since we are already waiting for something
        *RETURN_CODE = NO_ACTION;
        return;
    }

    // TODO: Do functionality for suspending a process

    process.PROCESS_STATE = WAITING;
    *RETURN_CODE = NO_ERROR;
}

void Process::RESUME(
    /*in */ PROCESS_ID_TYPE PROCESS_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    auto& process = status;
    if (process.PROCESS_STATE == PROCESS_STATE_TYPE::RUNNING) {
        // No action, since we are already running
        *RETURN_CODE = NO_ACTION;
        return;
    }

    // TODO: Do functionality for resuming a process

    process.PROCESS_STATE = PROCESS_STATE_TYPE::RUNNING;
    *RETURN_CODE = NO_ERROR;
}

void Process::STOP_SELF()
{
    // Get own process id
    PROCESS_ID_TYPE myId;
    RETURN_CODE_TYPE myCode;
    GET_MY_ID(&myId, &myCode);

    if (myCode != NO_ERROR) {
        // This means we haven't registered as a process
        return;
    }

    RETURN_CODE_TYPE stopReturn;
    STOP(myId, &stopReturn);
}

void Process::STOP(
    /*in */ PROCESS_ID_TYPE PROCESS_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    auto& process = status;
    if (process.PROCESS_STATE != PROCESS_STATE_TYPE::RUNNING) {
        // No action, is not running
        *RETURN_CODE = NO_ACTION;
        return;
    }

    // TODO: Do functionality for stopping a process

    process.PROCESS_STATE = PROCESS_STATE_TYPE::DORMANT;
    *RETURN_CODE = NO_ERROR;
}

void Process::START(
    /*in */ PROCESS_ID_TYPE PROCESS_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    auto& process = status;
    if (process.PROCESS_STATE == PROCESS_STATE_TYPE::RUNNING) {
        // No action, already running
        *RETURN_CODE = NO_ACTION;
        return;
    }

    // TODO: Do functionality for starting a process

    process.PROCESS_STATE = PROCESS_STATE_TYPE::RUNNING;
    *RETURN_CODE = NO_ERROR;
}

void Process::DELAYED_START(
    /*in */ PROCESS_ID_TYPE PROCESS_ID,
    /*in */ SYSTEM_TIME_TYPE DELAY_TIME,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    // TODO: Delay functionality here, for DELAY_TIME ticks

    RETURN_CODE_TYPE returnCode;
    START(PROCESS_ID, &returnCode);

    // If something went wrong
    if (returnCode != NO_ERROR) {
        *RETURN_CODE = INVALID_PARAM;
        return;
    }

    // Return the START code
    *RETURN_CODE = returnCode;
}

void Process::LOCK_PREEMPTION(
    /*out*/ LOCK_LEVEL_TYPE* LOCK_LEVEL,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    // TODO: Implement when preemption is done
}

void Process::UNLOCK_PREEMPTION(
    /*out*/ LOCK_LEVEL_TYPE* LOCK_LEVEL,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    // TODO: Implement when preemption is done
}

void Process::GET_MY_ID(
    /*out*/ PROCESS_ID_TYPE* PROCESS_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    if (id == INVALID_PROCESS_ID) {
        // The process has not been registered yet
        *RETURN_CODE = NOT_AVAILABLE;
    }

    *PROCESS_ID = id;
    *RETURN_CODE = NO_ERROR;
}

void Process::GET_PROCESS_ID(
    /*in */ PROCESS_NAME_TYPE PROCESS_NAME,
    /*out*/ PROCESS_ID_TYPE* PROCESS_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    PROCESS_ID_TYPE returnId;

    ApexKernel::getProcessIdByName(PROCESS_NAME, &returnId);

    if (returnId != NO_ERROR) {
        *RETURN_CODE = INVALID_PARAM;
    }

    *PROCESS_ID = returnId;
    *RETURN_CODE = NO_ERROR;
}

void Process::GET_PROCESS_STATUS(
    /*in */ PROCESS_ID_TYPE PROCESS_ID,
    /*out*/ PROCESS_STATUS_TYPE* PROCESS_STATUS,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    auto& process = status;

    if (process.ATTRIBUTES.ENTRY_POINT == nullptr) {
        *RETURN_CODE = INVALID_PARAM;
    }

    *PROCESS_STATUS = process;
    *RETURN_CODE = NO_ERROR;
}

void Process::INITIALIZE_PROCESS_CORE_AFFINITY(
    /*in */ PROCESS_ID_TYPE PROCESS_ID,
    /*in */ PROCESSOR_CORE_ID_TYPE PROCESSOR_CORE_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    // TODO: Implement, when multicore milestone is relevant
}

void Process::GET_MY_PROCESSOR_CORE_ID(
    /*in */ PROCESSOR_CORE_ID_TYPE PROCESSOR_CORE_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    // TODO: Implement, when multicore milestone is relevant
}

void Process::GET_MY_INDEX(
    /*in */ PROCESS_INDEX_TYPE PROCESS_INDEX,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    // TODO: Implement, when mutlicore milestone is relevant
}