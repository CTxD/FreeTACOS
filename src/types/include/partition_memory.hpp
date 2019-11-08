#ifndef PARTITION_MEMORY
#define PARTITION_MEMORY

#include "memory_requirements.hpp"


class PartitionMemory
{
  private:
    MemoryRegion memoryRegion[100];
    monotonic_buffer_resource memoryRegionSrc{std::data(memoryRegion),
                                              std::size(memoryRegion)};
    identifier_t partitionIdentifier;     /* required */
    std::optional<name_t> partitionName;  /* optional */
    vector<MemoryRegion> memoryRegions;    /* required */

  public:
    PartitionMemory(identifier_t id, name_t name, std::initializer_list<MemoryRegion> memory):
      partitionIdentifier(id), partitionName(name), memoryRegions(memory, &memoryRegionSrc) {}

    const identifier_t& getPartitionIdentifier() const;

    const std::optional<name_t>& getPartitionName() const;

    const vector<MemoryRegion>& getMemoryRegion() const;
};

#endif
