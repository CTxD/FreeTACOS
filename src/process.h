#include <general_types.h>

class Process
{
    private:
        NameType name;                                 /* required */
        std::optional<DecOrHexValueType> stacks_size;  /* optional */
        Criticality criticality_type = LEVEL_A;
        bool system_partition = false;
        NameType entry_point;                           /* required */
}