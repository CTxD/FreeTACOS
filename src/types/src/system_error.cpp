#include "include/system_error.hpp"

const identifier_t& SystemError::getErrorId() const
{
  return errorIdentifier;
}

const std::string& SystemError::getDescription() const
{
  return description;
}
