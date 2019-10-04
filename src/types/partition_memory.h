#include <optional>

#include "memory_requirements.h"

#ifndef PARTITION_MEMORY
#define PARTITION_MEMORY

class PartitionMemory
{
  private:
    identifierValueType partitionIdentifier;                                /* required */
    std::optional<nameType> partitionName;                                  /* optional */
    MemoryRequirements memoryRequirements[MAX_NUMBER_MEMORY_REQUIREMENTS];  /* required */
};

#endif
