#include "include/system_error.hpp"

const identifier_t& SystemError::getErrorId() const
{
  return errorIdentifier;
}

const description_t& SystemError::getDescription() const
{
  return description;
}
