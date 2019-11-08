#include "include/module_error_action.hpp"

const identifier_t& ModuleErrorAction::getErrorIdentifier() const
{
  return errorIdentifier;
}

const MODULE_RECOVERY_ACTION_TYPE& ModuleErrorAction::getAction() const
{
  return action;
}
