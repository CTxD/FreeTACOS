#ifndef PARTITION_MEMORY
#define PARTITION_MEMORY

#include "memory_requirements.hpp"

class PartitionMemory {
private:
    MemoryRegion memoryRegion[100];
    MemoryArea partitionMemoryArea{std::data(memoryRegion), std::size(memoryRegion)};
    MonotonicMemoryResource<> memoryRegionSrc{partitionMemoryArea};
    MonotonicAllocator<MemoryRegion> PartitionMemoryAllocator{memoryRegionSrc};

    identifier_t partitionIdentifier;       /* required */
    std::optional<NAME_TYPE> partitionName; /* optional */
    std::vector<MemoryRegion, MonotonicAllocator<MemoryRegion>> memoryRegions; /* required */

public:
    PartitionMemory(identifier_t id, NAME_TYPE name, std::initializer_list<MemoryRegion> memory)
        : partitionIdentifier(id), partitionName(name), memoryRegions(memory)
    {
    }

    const identifier_t& getPartitionIdentifier() const;

    const std::optional<NAME_TYPE>& getPartitionName() const;

    const std::vector<MemoryRegion, MonotonicAllocator<MemoryRegion>>& getMemoryRegion() const;
};

#endif
