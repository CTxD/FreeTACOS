#include "include/standard_partition.hpp"

const identifier_t& StandardPartition::getPartitionIdentifier() const
{
  return partitionIdentifier;
}

const name_t& StandardPartition::getPortName() const
{
  return portName;
}
