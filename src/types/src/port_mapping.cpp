#include "include/port_mapping.hpp"

const std::optional<PseudoPartition>& PortMapping::getPseudoPartition() const
{
    return pseudoPartition;
}

const std::optional<StandardPartition>& PortMapping::getStandardPartition() const
{
    return standardPartition;
}
