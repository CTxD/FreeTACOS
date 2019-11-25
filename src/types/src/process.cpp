#include "include/process.hpp"

const PROCESS_STATUS_TYPE& Process::getStatus() const
{
    return status;
}

const PROCESS_ATTRIBUTE_TYPE& Process::getAttributes() const
{
    return status.attributes;
}
