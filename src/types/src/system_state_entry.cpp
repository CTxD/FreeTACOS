#include "include/system_state_entry.hpp"

const APEX_INTEGER& SystemStateEntry::getSystemState() const
{
    return systemState;
}

const std::optional<NAME_TYPE> SystemStateEntry::getDescription() const
{
    return description;
}

const std::vector<ErrorLevel, MonotonicAllocator<ErrorLevel>>& SystemStateEntry::getErrorIdLevels() const
{
    return errorIdLevels;
}

const std::vector<ModuleErrorAction, MonotonicAllocator<ModuleErrorAction>>& SystemStateEntry::getActions() const
{
    return actions;
}
