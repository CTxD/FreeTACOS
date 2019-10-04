#include "general_types.h"
#include "system_state_entry.h"

#ifndef MODULE_HM_TABLE
#define MODULE_HM_TABLE

class ModuleHMTable
{
    private:
        std::optional<nameType> moduleCallback;     /* optional */
        SystemStateEntry systemStateEntry[MAX_NUMBER_SYSTEM_STATE_ENTRY];
};

#endif
