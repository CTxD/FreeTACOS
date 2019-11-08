#include "include/system_state_entry.hpp"

const APEX_INTEGER& SystemStateEntry::getSystemState() const
{
  return systemState;
}

const std::optional<name_t> SystemStateEntry::getDescription() const
{
  return description;
}

const vector<ErrorLevel>& SystemStateEntry::getErrorIdLevels() const
{
  return errorIdLevels;
}

const vector<ModuleErrorAction>& SystemStateEntry::getActions() const
{
  return actions;
}
