#include "include/process.hpp"

const PROCESS_ID_TYPE& Process::getId() const
{
    return id;
}

const PROCESS_INDEX_TYPE& Process::getIndex() const
{
    return index;
}

const PROCESS_STATUS_TYPE& Process::getStatus() const
{
    return status;
}

const PROCESS_ATTRIBUTE_TYPE& Process::getAttributes() const
{
    return status.attributes;
}
