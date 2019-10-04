#include "process.h"
#include "queuing_port.h"
#include "general_types.h"
#include "sampling_port.h"

#ifndef PARTITION
#define PARTITION

class PseudoPartition
{
  private:
    std::optional<nameType> name;                     /* optional */
    std::optional<decOrHexValueType> physicalAdress;  /* optional */
    std::optional<nameType> procedure;                /* optional */
};

class StandardPartition
{
  private:
    identifierValueType partitionIdentifier;  /* required */
    std::optional<nameType> partitionName;    /* optional */
    nameType portName;                        /* required */
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
        indentfierValueType partitionIdentifier;            /* required */
        std::optional<nameType> partitionName;              /* optional */
        CriticalityType criticality = LEVEL_A;
        bool systemPartition = false;
        char[MAXLENGTH] entryPoint;                         /* required */
        SamplingPort samplingPort[MAX_NUMBER_SAMPLING_PORT];
        QueuingPort queuingPort[MAX_NUMBER_QUEUING_PORT];
        Process process[MAX_NUMBER_PROCESS];
};

#endif
