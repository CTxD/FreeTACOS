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

  public:
    StandardPartition(IdentifierValueType id, NameType name):
      partitionIdentifier(id), portName(name) {}
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

  typedef
    enum AffinityType
    {
      ANY     = 0,
      CORE_1  = 1,
      CORE_2  = 2,
      CORE_3  = 3,
      CORE_4  = 4,
    };

class Partition
{
    private:
        IndentfierValueType partitionIdentifier;/* required */
        std::optional<NameType> partitionName;  /* optional */
        CriticalityType criticality = LEVEL_A;  /* required */
        bool systemPartition = false;           /* required */
        char* entryPoint;                       /* required */
        SamplingPort* samplingPort;             /* required */
        QueuingPort* queuingPort;               /* required */
        Process* process;                       /* required */

      public:
        Partition(IdentifierValueType id, NameType name, CriticalityType critical,
                  bool systemPartition, char* entry, SamplingPort* sampling,
                  QueuingPort queuing, Process* process):
                  partitionIdentifier(id), partitionName(name), criticality(critical),
                  systemPartition(systemPartition), entryPoint(entry), samplingPort(sampling),
                  queuingPort(queuing), process(process) {}
};

#endif
