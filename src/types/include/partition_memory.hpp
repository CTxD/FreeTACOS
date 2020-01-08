#ifndef PARTITION_MEMORY
#define PARTITION_MEMORY

#include "memory_requirements.hpp"

class PartitionMemory {
private:
    MemoryRegion memoryRegion[100];
    std::vector<MemoryRegion>* memoryRegions = new (&memoryRegion) std::vector<MemoryRegion>;

    identifier_t partitionIdentifier;    /* required */
    std::optional<name_t> partitionName; /* optional */

public:
    PartitionMemory(identifier_t id, name_t name, std::initializer_list<MemoryRegion> memory)
        : partitionIdentifier(id), partitionName(name)
    {
        for (auto m : memory) {
            memoryRegions->push_back(m);
        }
    }

    const identifier_t& getPartitionIdentifier() const;

    const std::optional<name_t>& getPartitionName() const;

    const vector<MemoryRegion>& getMemoryRegion() const;
};

#endif
