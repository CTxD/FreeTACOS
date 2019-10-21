#ifndef ERROR_ACTION
#define ERROR_ACTION

#include "error_level.h"
#include "general_types.h"


class ErrorAction
{
    private:
        identifier_t errorIdentifier;           /* required */
        MODULE_RECOVERY_ACTION_TYPE action;     /* required */
        std::optional<ERROR_LEVEL_TYPE> level;  /* optional */

        // Deprecated
        std::optional<name_t> description;      /* optional */

    public:
        ErrorAction(identifier_t id, MODULE_RECOVERY_ACTION_TYPE action, ERROR_LEVEL_TYPE level):
          errorIdentifier(id), action(action), level(level) {}
};

#endif
