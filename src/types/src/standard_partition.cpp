#include "standard_partition.hpp"

const identifier_t& StandardPartition::getPartitionIdentifier() const
{
  return partitionIdentifier;
}

const NAME_TYPE& StandardPartition::getPortName() const
{
  return portName;
}
