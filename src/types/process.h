#include <optional>

#include "general_types.h"

#ifndef PROCESS
#define PROCESS

class Process
{
    private:
        nameType name;                                  /* required */
        std::optional<decOrHexValueType> stacksSize;    /* optional */
        Criticality criticalityType = LEVEL_A;
        bool systemPartition = false;
        nameType entryPoint;                            /* required */
};

#endif
