#ifndef PARTITION
#define PARTITION

#include "process.h"
#include "port_type.h"
#include "general_types.h"

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
        IdentifierValueType partitionIdentifier;/* required */
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
                  QueuingPort* queuing, Process* process):
                  partitionIdentifier(id), partitionName(name), criticality(critical),
                  systemPartition(systemPartition), entryPoint(entry), samplingPort(sampling),
                  queuingPort(queuing), process(process) {}
};

#endif
