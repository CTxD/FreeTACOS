#include "include/partition_memory.hpp"

const identifier_t& PartitionMemory::getPartitionIdentifier() const
{
  return partitionIdentifier;
}

const std::optional<NAME_TYPE>& PartitionMemory::getPartitionName() const
{
  return partitionName;
}

const std::vector<MemoryRegion>& PartitionMemory::getMemoryRegion() const
{
  return memoryRegions;
}
