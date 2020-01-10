#ifndef PARTITION_ERROR_ACTION
#define PARTITION_ERROR_ACTION

#include "apex_partition.h"
#include "error_level.hpp"

class PartitionErrorAction {
private:
    identifier_t errorIdentifier;          /* required */
    PARTITION_RECOVERY_ACTION_TYPE action; /* required */
    ERROR_LEVEL_TYPE level;                /* required */
    ERROR_CODE_TYPE code;                  /* required */

public:
    PartitionErrorAction()
    {
    }

    PartitionErrorAction(identifier_t id,
                         PARTITION_RECOVERY_ACTION_TYPE action,
                         ERROR_LEVEL_TYPE level,
                         ERROR_CODE_TYPE code)
        : errorIdentifier(id), action(action), level(level), code(code)
    {
    }

    const identifier_t& getErrorIdentifier() const;

    const PARTITION_RECOVERY_ACTION_TYPE& getAction() const;

    const ERROR_LEVEL_TYPE& getLevel() const;

    const ERROR_CODE_TYPE& getCode() const;
};

#endif
