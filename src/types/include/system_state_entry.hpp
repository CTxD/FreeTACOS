#ifndef SYSTEM_STATE_ENTRY
#define SYSTEM_STATE_ENTRY

#include "error_level.hpp"
#include "module_error_action.hpp"

class SystemStateEntry {
private:
    ErrorLevel errorLevel[100];
    MemoryArea errorLevelArea{std::data(errorLevel), std::size(errorLevel)};
    MonotonicMemoryResource<> errorLevelSrc{errorLevelArea};
    MonotonicAllocator<ErrorLevel> errorLevelAllocator{errorLevelSrc};

    ModuleErrorAction moduleErrorAction[100];
    MemoryArea moduleErrorActionArea{std::data(moduleErrorAction),
                                     std::size(moduleErrorAction)};
    MonotonicMemoryResource<> moduleErrorActionSrc{moduleErrorActionArea};
    MonotonicAllocator<ModuleErrorAction> moduleErrorActionAllocator{moduleErrorActionSrc};
    APEX_INTEGER systemState;             /* required */
    std::optional<NAME_TYPE> description; /* optional */
    std::vector<ErrorLevel, MonotonicAllocator<ErrorLevel>> errorIdLevels{errorLevelAllocator}; /* required */
    std::vector<ModuleErrorAction, MonotonicAllocator<ModuleErrorAction>> actions{
        moduleErrorActionAllocator}; /* required */

public:
    SystemStateEntry(){};

    SystemStateEntry(const int state,
                     const NAME_TYPE descr,
                     std::initializer_list<ErrorLevel> levels,
                     std::initializer_list<ModuleErrorAction> actions)
        : systemState(state), description(descr), errorIdLevels(levels), actions(actions)
    {
    }

    const APEX_INTEGER& getSystemState() const;

    const std::optional<NAME_TYPE> getDescription() const;

    const std::vector<ErrorLevel, MonotonicAllocator<ErrorLevel>>& getErrorIdLevels() const;

    const std::vector<ModuleErrorAction, MonotonicAllocator<ModuleErrorAction>>& getActions() const;
};

#endif
