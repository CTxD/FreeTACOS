#include "partition_error_action.hpp"

const identifier_t& PartitionErrorAction::getErrorIdentifier() const
{
  return errorIdentifier;
}

const PARTITION_RECOVERY_ACTION_TYPE& PartitionErrorAction::getAction() const
{
  return action;
}

const ERROR_LEVEL_TYPE& PartitionErrorAction::getLevel() const
{
  return level;
}

const ERROR_CODE_TYPE& PartitionErrorAction::getCode() const
{
  return code;
}
