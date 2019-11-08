#include "include/multipartition_error_action.hpp"

const identifier_t& MultiPartitionErrorAction::getErrorId() const
{
  return errorIdentifier;
}

const ERROR_LEVEL_TYPE& MultiPartitionErrorAction::getLevel() const
{
  return level;
}

const std::optional<MODULE_RECOVERY_ACTION_TYPE>& MultiPartitionErrorAction::getAction() const
{
  return action;
}
