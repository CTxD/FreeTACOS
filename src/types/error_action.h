#ifndef ERROR_ACTION
#define ERROR_ACTION

#include "error_level.h"
#include "general_types.h"

enum recovery_action_t
{
    IGNORE      = 0,
    SHUTDOWN    = 1,
    RESET       = 2,
};

class ErrorAction
{
    private:
        identifier_t errorIdentifier;       /* required */
        recovery_action_t action;           /* required */
        std::optional<error_level_t> level; /* optional */

        // Deprecated
        std::optional<name_t> description;  /* optional */

    public:
        ErrorAction(identifier_t id,  recovery_action_t action, error_level_t level):
          errorIdentifier(id), action(action), level(level) {}
};

#endif
