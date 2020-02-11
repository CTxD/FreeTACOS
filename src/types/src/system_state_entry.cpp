#include "system_state_entry.hpp"

const APEX_INTEGER& SystemStateEntry::getSystemState() const
{
  return systemState;
}

const std::optional<name_t> SystemStateEntry::getDescription() const
{
  return description;
}

const std::vector<ErrorLevel>& SystemStateEntry::getErrorIdLevels() const
{
  return *errorLevels;
}

const std::vector<ModuleErrorAction>& SystemStateEntry::getActions() const
{
  return *moduleErrorActions;
}
