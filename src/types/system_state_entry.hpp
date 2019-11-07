#ifndef SYSTEM_STATE_ENTRY
#define SYSTEM_STATE_ENTRY

#include "error_level.h"
#include "module_error_action.h"


class SystemStateEntry
{
    private:
       APEX_INTEGER systemState;                    /* required */
        std::optional<name_t> description;  /* optional */
        vector<ErrorLevel> errorIdLevel;    /* required */
        vector<ModuleErrorAction> actions;  /* required */

    public:
      SystemStateEntry(const APEX_INTEGER state, const name_t descr,
                       vector<ErrorLevel> levels, vector<ModuleErrorAction> actions):
        systemState(std::move(state)), description(std::move(descr)),
        errorIdLevel(std::move(levels)), actions(std::move(actions)) {}
};

#endif
