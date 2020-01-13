#include "include/error_level.hpp"

const identifier_t& ErrorLevel::getErrorIdentifier() const
{
  return errorIdentifier;
}

const std::optional<NAME_TYPE>& ErrorLevel::getDescription() const
{
  return description;
}

const ERROR_LEVEL_TYPE& ErrorLevel::getErrorLevel() const
{
  return error_level;
}

const std::optional<ERROR_CODE_TYPE>& ErrorLevel::getErrorCode() const
{
  return error_code;
}
