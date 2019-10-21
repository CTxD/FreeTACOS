#ifndef ERROR_ACTION
#define ERROR_ACTION

#include "error_level.h"
#include "general_types.h"


class MultiPartitionErrorAction
{
    private:
        identifier_t errorIdentifier;                       /* required */
        ERROR_LEVEL_TYPE level;                            /* required */
        std::optional<MODULE_RECOVERY_ACTION_TYPE> action;  /* optional */

    public:
        MultiPartitionErrorAction(identifier_t id, ERROR_LEVEL_TYPE level, MODULE_RECOVERY_ACTION_TYPE action):
          errorIdentifier(id), action(action), level(level) {}
};

class PartitionErrorAction
{
    private:
        identifier_t errorIdentifier;            /* required */
        PARTITION_RECOVERY_ACTION_TYPE action;   /* required */
        ERROR_LEVEL_TYPE level;                  /* required */
        ERROR_CODE_TYPE code;                    /* required */

    public:
        PartitionErrorAction(identifier_t id, PARTITION_RECOVERY_ACTION_TYPE action, ERROR_LEVEL_TYPE level, ERROR_CODE_TYPE code):
          errorIdentifier(id), action(action), level(level), code(code) {}
};

class ModuleErrorAction
{
    private:
        identifier_t errorIdentifier;        /* required */
        MODULE_RECOVERY_ACTION_TYPE action;  /* required */

    public:
        ModuleErrorAction(identifier_t id, MODULE_RECOVERY_ACTION_TYPE action):
          errorIdentifier(id), action(action) {}
};


#endif
