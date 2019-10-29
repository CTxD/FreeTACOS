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
    SystemError(identifier_t id, std::string descr):
      errorIdentifier(id), description(descr) {}
};

// Deprecated
class SystemStateEntry
{
    private:
        int systemState;                          /* required */
        std::optional<name_t> description;        /* optional */
        std::vector<ErrorLevel> errorIdLevel;     /* required */
        std::vector<ModuleErrorAction> actions;   /* required */

    public:
      SystemStateEntry(const int state, const name_t descr,
                       std::vector<ErrorLevel> levels, std::vector<ModuleErrorAction> actions):
        systemState(std::move(state)), description(std::move(descr)),
        errorIdLevel(std::move(levels)), actions(std::move(actions)) {}
};

#endif
