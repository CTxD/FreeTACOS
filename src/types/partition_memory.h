#include <optional>

#include "memory_requirements.h"

#ifndef PARTITION_MEMORY
#define PARTITION_MEMORY

class PartitionMemory
{
  private:
    IdentifierValueType partitionIdentifier;  /* required */
    std::optional<NameType> partitionName;    /* optional */
    MemoryRequirements* memoryRequirements;   /* required */

  public:
    PartitionMemory(IdentifierValueType id, NameType name, MemoryRequirements* reqs):
      partitionIdentifier(id), partitionName(name), memoryRequirements(reqs) {}
};

#endif
