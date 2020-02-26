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

const PROCESS_STATUS_TYPE& Process::getStatus() const
{
    return processStatus;
}

const PROCESS_ATTRIBUTE_TYPE& Process::getAttributes() const
{
    return processStatus.ATTRIBUTES;
}

const PROCESS_NAME_TYPE& Process::getProcessIdentifier() const
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
    addToProcessList(static_cast<Task*>(ATTRIBUTES->ENTRY_POINT));
    *PROCESS_ID = 10;
    *RETURN_CODE = NO_ERROR;
}