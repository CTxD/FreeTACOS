#include "include/pseudo_partition.hpp"

const std::optional<NAME_TYPE>& PseudoPartition::getName() const
{
  return name;
}

const std::optional<decOrHex_t>& PseudoPartition::getPhysicalAddress() const
{
  return physicalAddress;
}

const std::optional<NAME_TYPE>& PseudoPartition::getProcedure() const
{
  return procedure;
}
