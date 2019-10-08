#ifndef PROCESS
#define PROCESS

#include "general_types.h"

class Process
{
    private:
        NameType name;                                /* required */
        std::optional<DecOrHexValueType> stackSize;   /* optional */
        CriticalityType criticalityType = LEVEL_A;    /* required */
        bool systemPartition = false;                 /* required */
        NameType entryPoint;                          /* required */

    public:
        Process(NameType& name, DecOrHexValueType size, CriticalityType critical,
                bool systemPartition, NameType& entry):
          name(std::move(name)), stackSize(size), criticalityType(critical),
          systemPartition(systemPartition), entryPoint(std::move(entry)) {}
};

#endif
