#include "process.hpp"

const PROCESS_STATUS_TYPE& Process::getStatus() const
{
  return status;
}

const PROCESS_ATTRIBUTE_TYPE& Process::getAttributes() const
{
  return status.ATTRIBUTES;
}

const decOrHex_t& Process::getProcessIdentifier() const
{
  return processIdentifier;
}