#include "general_types.h"
#include "system_state_entry.h"

#ifndef MODULE_HM_TABLE
#define MODULE_HM_TABLE

class ModuleHMTable
{
    private:
      std::optional<NameType> moduleCallback;     /* optional */
      SystemStateEntry* systemStateEntry;         /* required */

    public:
      ModuleHMTable(NameType callback, SystemStateEntry* entry):
        moduleCallback(callback), systemStateEntry(entry) {}
};

#endif
