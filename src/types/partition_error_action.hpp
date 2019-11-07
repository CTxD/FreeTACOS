#ifndef PARTITION_ERROR_ACTION
#define PARTITION_ERROR_ACTION

#include "error_level.h"
#include "apex_partition.h"


class PartitionErrorAction
{
    private:
        identifier_t errorIdentifier;            /* required */
        PARTITION_RECOVERY_ACTION_TYPE action;   /* required */
        ERROR_LEVEL_TYPE level;                  /* required */
        ERROR_CODE_TYPE code;                    /* required */

    public:
        PartitionErrorAction(identifier_t id, PARTITION_RECOVERY_ACTION_TYPE action,
                             ERROR_LEVEL_TYPE level, ERROR_CODE_TYPE code):
          errorIdentifier(id), action(action), level(level), code(code) {}

        identifier_t getErrorIdentifier();

        PARTITION_RECOVERY_ACTION_TYPE getAction();

        ERROR_LEVEL_TYPE getLevel();

        ERROR_CODE_TYPE getCode();
};

#endif
