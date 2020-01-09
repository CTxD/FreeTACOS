#include "include/module_hm_table.hpp"

ModuleHMTable& ModuleHMTable::operator=(const ModuleHMTable& rhs)
{
  stateIdentifier = rhs.stateIdentifier;
  strcpy(description, rhs.description);
  moduleErrorActions = rhs.moduleErrorActions;
  return *this;
}

const identifier_t& ModuleHMTable::getStateIdentifier() const
{
  return stateIdentifier;
}

const description_t& ModuleHMTable::getDescription() const
{
  return description;
}

const std::vector<ModuleErrorAction>& ModuleHMTable::getActions() const
{
  return *moduleErrorActions;
}
