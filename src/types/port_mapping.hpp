#ifndef PORT_MAPPING
#define PORT_MAPPING

#include "pseudo_partition.h"
#include "standard_partition.h"

class PortMappingType
{
  private:
    std::optional<PseudoPartition> pseudoPartition;     /* optional */
    std::optional<StandardPartition> standardPartition; /* optional */

  public:
    PortMappingType(PseudoPartition pseudoPart): pseudoPartition(std::move(pseudoPart)) {}

    PortMappingType(StandardPartition standardPart): standardPartition(std::move(standardPart)) {}

    std::optional<PseudoPartition> getPseudoPartition();

    std::optional<StandardPartition> getStandardPartition();
};

#endif
