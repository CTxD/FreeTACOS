#include "include/pseudo_partition.hpp"

const std::optional<name_t>& PseudoPartition::getName() const
{
  return name;
}

const std::optional<decOrHex_t>& PseudoPartition::getPhysicalAddress() const
{
  return physicalAddress;
}

const std::optional<name_t>& PseudoPartition::getProcedure() const
{
  return procedure;
}
