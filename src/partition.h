#include "process.h"
#include "queuing_port.h"
#include "general_types.h"
#include "sampling_port.h"

#ifndef PARTITION
#define PARTITION

class PseudoPartition
{
  private:
    std::optional<NameType> name;                     /* optional */
    std::optional<DecOrHexValueType> physicalAdress;  /* optional */
    std::optional<NameType> procedure;                /* optional */
};

class StandardPartition
{
  private:
    IdentifierValueType partitionIdentifier;  /* required */
    std::optional<NameType> partitionName;    /* optional */
    NameType portName;                        /* required */
    std::optional<int> physicalAdress;        /* optional */
};

typedef
    enum CriticalityType
    {
        LEVEL_A = 0,
        LEVEL_B = 1,
        LEVEL_C = 2,
        LEVEL_D = 3,
        LEVEL_E = 4,
    };

class Partition
{
    private:
        IndentfierValueType partition_identifier;       /* required */
        std::optional<NameType> partition_name;        /* optional */
        CriticalityType criticality = LEVEL_A;
        bool system_partition = false;
        char[MAXLENGTH] entry_point;                    /* required */
        SamplingPort sampling_port[MAX_NUMBER_SAMPLING_PORT];
        QueuingPort queuing_port[MAX_NUMBER_QUEUING_PORT];
        Process process[MAX_NUMBER_PROCESS];
};

#endif
