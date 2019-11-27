#ifndef SYSTEM_STATE_ENTRY
#define SYSTEM_STATE_ENTRY

#include "error_level.hpp"
#include "module_error_action.hpp"


class SystemStateEntry
{
    private:
      ErrorLevel errorLevel[100];
      monotonic_buffer_resource errorLevelSrc{std::data(errorLevel),
                                              std::size(errorLevel)};
      ModuleErrorAction moduleErrorAction[100];
      monotonic_buffer_resource moduleErrorActionSrc{std::data(moduleErrorAction),
                                                     std::size(moduleErrorAction)};
      APEX_INTEGER systemState;                          /* required */
      std::optional<name_t> description;        /* optional */
      vector<ErrorLevel> errorIdLevels;          /* required */
      vector<ModuleErrorAction> actions;        /* required */

    public:
      SystemStateEntry() {};

      SystemStateEntry(const int state, const name_t descr,
                       std::initializer_list<ErrorLevel> levels,
                       std::initializer_list<ModuleErrorAction> actions):
        systemState(state), description(descr),
        errorIdLevels(levels, &errorLevelSrc),
        actions(actions, &moduleErrorActionSrc) {}

      const APEX_INTEGER& getSystemState() const;

      const std::optional<name_t> getDescription() const;

      const vector<ErrorLevel>& getErrorIdLevels() const;

      const vector<ModuleErrorAction>& getActions() const;
};

#endif
