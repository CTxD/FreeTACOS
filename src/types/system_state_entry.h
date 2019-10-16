#ifndef SYSTEM_STATE_ENTRY
#define SYSTEM_STATE_ENTRY

#include "error_id_level.h"
#include "error_id_action.h"

class SystemStateEntry
{
    private:
        int systemState;                      /* required */
        std::optional<NameType> description;  /* optional */
        ErrorIDLevel errorIdLevel;            /* required */
        ErrorIDAction errorIdAction;          /* required */

    public:
      SystemStateEntry(const int state, const NameType descr, int numLevels, ErrorIDLevel levels, int numActions, ErrorIDAction actions):
        systemState(std::move(state)), description(std::move(descr)), errorIdLevel(std::move(levels)), errorIdAction(std::move(actions)) {}

      SystemStateEntry(const int state, ErrorIDLevel levels, ErrorIDAction actions):
        systemState(std::move(state)), errorIdLevel(std::move(levels)), errorIdAction(std::move(actions)) {}
};

#endif
