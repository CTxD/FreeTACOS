#ifndef SYSTEM_STATE_ENTRY
#define SYSTEM_STATE_ENTRY

#include "error_level.hpp"
#include "module_error_action.hpp"

class SystemStateEntry {
private:
    ErrorLevel errorLevel[1];
    std::vector<ErrorLevel>* errorLevels = new (&errorLevel) std::vector<ErrorLevel>;

    ModuleErrorAction moduleErrorAction[1];
    std::vector<ModuleErrorAction>* moduleErrorActions =
        new (&moduleErrorAction) std::vector<ModuleErrorAction>;

    APEX_INTEGER systemState;          /* required */
    std::optional<name_t> description; /* optional */

public:
    SystemStateEntry(){};

    SystemStateEntry(const int state,
                     const name_t descr,
                     std::initializer_list<ErrorLevel> levels,
                     std::initializer_list<ModuleErrorAction> actions)
        : systemState(state), description(descr)
    {
        for (auto l : levels) {
            errorLevels->push_back(l);
        }
        for (auto a : actions) {
            moduleErrorActions->push_back(a);
        }
    }

    const APEX_INTEGER& getSystemState() const;

    const std::optional<name_t> getDescription() const;

    const std::vector<ErrorLevel>& getErrorIdLevels() const;

    const std::vector<ModuleErrorAction>& getActions() const;
};

#endif
