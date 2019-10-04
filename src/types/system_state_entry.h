#include "general_types.h"
#include "error_id_level.h"
#include "error_id_action.h"


#ifndef SYSTEM_STATE_ENTRY
#define SYSTEM_STATE_ENTRY

class SystemStateEntry
{
    private:
        int systemState;                        /* required */
        std::optional<nameType> description;    /* optional */
        ErrorIDLevel errorIdLevel[MAX_NUMBER_ERROR_ID_LEVEL];
        ErrorIDAction errorIdAction[MAX_NUMBER_ERROR_ID_ACTION];
};

#endif
