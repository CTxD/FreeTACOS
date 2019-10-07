#include <optional>

#include "general_types.h"

#ifndef PROCESS
#define PROCESS

class Process
{
    private:
        NameType name;                                /* required */
        std::optional<DecOrHexValueType> stackSize;   /* optional */
        Criticality criticalityType = LEVEL_A;        /* required */
        bool systemPartition = false;                 /* required */
        NameType entryPoint;                          /* required */

    public:
        Process(NameType name, DecOrHexValueType size, Criticality critical,
                bool systemPartition, NameType entryPoint):
          name(name), stackSize(size), criticalityType(critical),
          systemPartition(systemPartition), entryPoint(entry) {}
};

#endif
