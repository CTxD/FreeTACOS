#ifndef PORT_MAPPING
#define PORT_MAPPING

#include "pseudo_partition.hpp"
#include "standard_partition.hpp"

class PortMappingType
{
  private:
    std::optional<PseudoPartition> pseudoPartition;     /* optional */
    std::optional<StandardPartition> standardPartition; /* optional */

  public:
    PortMappingType() {};
    PortMappingType(PseudoPartition pseudoPart): pseudoPartition(std::move(pseudoPart)) {}

    PortMappingType(StandardPartition standardPart): standardPartition(std::move(standardPart)) {}

    std::optional<PseudoPartition> getPseudoPartition();

    std::optional<StandardPartition> getStandardPartition();
};

#endif
