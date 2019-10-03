#include <optional>

#include "memory_requirements.h"

class PartitionMemory {
  private:
    IdentifierValueType partitionIdentifier;  /* required */
    std::optional<NameType> partitionName;    /* optional */
    MemoryRequirements memoryRequirements[MAX_NUMBER_MEMORY_REQUIREMENTS]; /* required */
}
