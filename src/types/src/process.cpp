#include "process.hpp"

Process::Process(PROCESS_ATTRIBUTE_TYPE& attributes)
{
    processStatus.ATTRIBUTES = attributes;
    processStatus.CURRENT_PRIORITY = attributes.BASE_PRIORITY;
    processStatus.DEADLINE_TIME = attributes.TIME_CAPACITY;
    processStatus.PROCESS_STATE = PROCESS_STATE_TYPE::DORMANT;
}

Process::Process(PROCESS_STATUS_TYPE& status)
{
    processStatus = status;
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