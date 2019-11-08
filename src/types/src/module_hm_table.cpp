#include "include/module_hm_table.hpp"

ModuleHMTable& ModuleHMTable::operator=(const ModuleHMTable& rhs)
{
  stateIdentifier = rhs.stateIdentifier;
  description = rhs.description;
  actions = rhs.actions;
  return *this;
}

const identifier_t& ModuleHMTable::getStateIdentifier() const
{
  return stateIdentifier;
}

const std::string& ModuleHMTable::getDescription() const
{
  return description;
}

const vector<ModuleErrorAction>& ModuleHMTable::getActions() const
{
  return actions;
}
