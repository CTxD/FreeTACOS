#include <general_types.h>
#include <system_state_entry.h>

class ModuleHMTable
{
    private:
        std::optional <NameType> ModuleCallback;     /* optional */
        SystemStateEntry system_state_entry[MAX_NUMBER_SYSTEM_STATE_ENTRY];
}