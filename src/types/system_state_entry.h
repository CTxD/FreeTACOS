#ifndef SYSTEM_STATE_ENTRY
#define SYSTEM_STATE_ENTRY

#include "error_level.h"
#include "error_action.h"


class SystemError
{
  private:
    identifier_t errorIdentifier; /* required */
    std::string description;      /* required */

  public:
    SystemError() {};
    SystemError(identifier_t id, std::string descr):
      errorIdentifier(id), description(descr) {}
};

// Deprecated
class SystemStateEntry
{
    private:
      ErrorLevel errorLevel[100];
      monotonic_buffer_resource errorLevelSrc{std::data(errorLevel),
                                                    std::size(errorLevel)};
      ModuleErrorAction moduleErrorAction[100];
      monotonic_buffer_resource moduleErrorActionSrc{std::data(moduleErrorAction),
                                                    std::size(moduleErrorAction)};
      int systemState;                          /* required */
      std::optional<name_t> description;        /* optional */
      vector<ErrorLevel> errorIdLevel;          /* required */
      vector<ModuleErrorAction> actions;        /* required */

    public:
      SystemStateEntry() {};
      SystemStateEntry(const int state, const name_t descr,
                       std::initializer_list<ErrorLevel> levels,
                       std::initializer_list<ModuleErrorAction> actions):
        systemState(state), description(descr),
        errorIdLevel(levels, &errorLevelSrc), actions(actions, &moduleErrorActionSrc) {}
};

#endif
