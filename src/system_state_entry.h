#include "general_types.h"
#include "error_id_level.h"
#include "error_id_action.h"


#ifndef SYSTEM_STATE_ENTRY
#define SYSTEM_STATE_ENTRY

class SystemStateEntry
{
    private:
        int systemState;                      /* required */
        std::optional<NameType> description;  /* optional */
        ErrorIDLevel* errorIdLevel;           /* required */
        ErrorIDAction* errorIdAction;         /* required */

    public:
      SystemStateEntry(int state, NameType descr, ErrorIDLevel* levels, ErrorIDAction* actions):
        systemState(state), description(descr), errorIdLevel(levels), errorIdAction(actions) {}
};

#endif
