#include "process.hpp"
#include "apex_kernel.hpp"

Process::Process(PROCESS_ATTRIBUTE_TYPE& attributes)
{
    processStatus.ATTRIBUTES = attributes;
    processStatus.CURRENT_PRIORITY = attributes.BASE_PRIORITY;
    processStatus.DEADLINE_TIME = attributes.TIME_CAPACITY;
    processStatus.PROCESS_STATE = PROCESS_STATE_TYPE::DORMANT;
}

Process::Process(PROCESS_STATUS_TYPE& status) : processStatus(status)
{
}

PROCESS_STATUS_TYPE& Process::getStatus()
{
    return processStatus;
}

PROCESS_ATTRIBUTE_TYPE& Process::getAttributes()
{
    return processStatus.ATTRIBUTES;
}

PROCESS_NAME_TYPE& Process::getProcessIdentifier()
{
    return processStatus.ATTRIBUTES.NAME;
}

PROCESS_STATE_TYPE& Process::getProcessState()
{
    return processStatus.PROCESS_STATE;
}

void Process::setProcessState(PROCESS_STATE_TYPE& state)
{
    processStatus.PROCESS_STATE = state;
}

/* APEX Functionality Below */
void Process::CREATE_PROCESS(
    /*in */ PROCESS_ATTRIBUTE_TYPE* ATTRIBUTES,
    /*out*/ PROCESS_ID_TYPE* PROCESS_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    ApexKernel::addToProcessList(static_cast<Task*>(ATTRIBUTES->ENTRY_POINT));
    *PROCESS_ID = 10;
    *RETURN_CODE = NO_ERROR;
}
void Process::SET_PRIORITY(
    /*in */ PROCESS_ID_TYPE PROCESS_ID,
    /*in */ PRIORITY_TYPE PRIORITY,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    auto& process = ApexKernel::getProcessById(PROCESS_ID);
    if (process.CURRENT_PRIORITY == PRIORITY) {
        // No action, since the prioties are the same
        *RETURN_CODE = NO_ACTION;
        return;
    }

    ApexKernel::getProcessById(PROCESS_ID).CURRENT_PRIORITY = PRIORITY;
    *RETURN_CODE = NO_ERROR;
}

void Process::SUSPEND_SELF(
    /*in */ SYSTEM_TIME_TYPE TIME_OUT,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    // Do some timing here, and set the mode to suspended, until time has passed.

    // Get own process id
    PROCESS_ID_TYPE* myId = nullptr;
    RETURN_CODE_TYPE* myCode = nullptr;
    GET_MY_ID(myId, myCode);

    // Check if i exist
    if (*myCode != NO_ERROR) {
        *RETURN_CODE = INVALID_PARAM;
        return;
    }

    // Suspend myself
    RETURN_CODE_TYPE* returnCode = nullptr;
    SUSPEND(*myId, returnCode);

    // Check if SUSPEND was successful
    if (returnCode == nullptr) {
        *returnCode = RETURN_CODE_TYPE::NOT_AVAILABLE;
        return;
    }

    // Should be NO_ERROR, if SUSPEND was successful
    RETURN_CODE = returnCode;
}

void Process::SUSPEND(
    /*in */ PROCESS_ID_TYPE PROCESS_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    auto& process = ApexKernel::getProcessById(PROCESS_ID);
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
    auto& process = ApexKernel::getProcessById(PROCESS_ID);
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
    PROCESS_ID_TYPE* myId = nullptr;
    RETURN_CODE_TYPE* myCode = nullptr;
    GET_MY_ID(myId, myCode);

    STOP(*myId, nullptr);
}

void Process::STOP(
    /*in */ PROCESS_ID_TYPE PROCESS_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    auto& process = ApexKernel::getProcessById(PROCESS_ID);
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
    auto& process = ApexKernel::getProcessById(PROCESS_ID);
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

    RETURN_CODE_TYPE* returnCode = nullptr;
    START(PROCESS_ID, returnCode);

    // If something went wrong
    if (returnCode == nullptr) {
        *RETURN_CODE = INVALID_PARAM;
        return;
    }

    // Return the START code
    RETURN_CODE = returnCode;
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
    PROCESS_ID_TYPE* returnId = nullptr;

    ApexKernel::getProcessIdByName(getAttributes().NAME, returnId);

    if (returnId == nullptr) {
        *RETURN_CODE = INVALID_PARAM;
    }

    PROCESS_ID = returnId;
    *RETURN_CODE = NO_ERROR;
}

void Process::GET_PROCESS_ID(
    /*in */ PROCESS_NAME_TYPE PROCESS_NAME,
    /*out*/ PROCESS_ID_TYPE* PROCESS_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    PROCESS_ID_TYPE* returnId = nullptr;

    ApexKernel::getProcessIdByName(PROCESS_NAME, returnId);

    if (returnId == nullptr) {
        *RETURN_CODE = INVALID_PARAM;
    }

    PROCESS_ID = returnId;
    *RETURN_CODE = NO_ERROR;
}

void Process::GET_PROCESS_STATUS(
    /*in */ PROCESS_ID_TYPE PROCESS_ID,
    /*out*/ PROCESS_STATUS_TYPE* PROCESS_STATUS,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    auto& process = ApexKernel::getProcessById(PROCESS_ID);

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