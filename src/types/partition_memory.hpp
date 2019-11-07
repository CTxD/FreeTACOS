#ifndef PARTITION_MEMORY
#define PARTITION_MEMORY

#include "memory_requirements.h"


class PartitionMemory
{
  private:
    identifier_t partitionIdentifier;     /* required */
    std::optional<name_t> partitionName;  /* optional */
    vector<MemoryRegion> memoryRegion;    /* required */

  public:
    PartitionMemory(identifier_t id, name_t name, std::initializer_list<MemoryRegion> memory):
      partitionIdentifier(id), partitionName(name), memoryRegion(memory) {}

    identifier_t getPartitionIdentifier();

    name_t getPartitionName();

    vector<MemoryRegion> getMemoryRegion();    
};

#endif
