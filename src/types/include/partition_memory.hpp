#ifndef PARTITION_MEMORY
#define PARTITION_MEMORY

#include "memory_requirements.hpp"

class PartitionMemory {
private:
    MemoryRegion memoryRegion[100];
    std::vector<MemoryRegion>* memoryRegions = new (&memoryRegion) std::vector<MemoryRegion>;

    identifier_t partitionIdentifier;       /* required */
    std::optional<NAME_TYPE> partitionName; /* optional */

public:
    PartitionMemory(identifier_t id, NAME_TYPE name, std::initializer_list<MemoryRegion> memory)
        : partitionIdentifier(id), partitionName(name)
    {
        for (auto m : memory) {
            memoryRegions->push_back(m);
        }
    }

    const identifier_t& getPartitionIdentifier() const;

    const std::optional<NAME_TYPE>& getPartitionName() const;

    const std::vector<MemoryRegion>& getMemoryRegion() const;
};

#endif
