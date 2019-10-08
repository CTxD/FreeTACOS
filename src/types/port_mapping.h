#ifndef PORT_MAPPING_TYPE
#define PORT_MAPPING_TYPE

#include "pseudo_standard_partitions.h"

class PortMappingType
{
  private:
    std::optional<PseudoPartition> pseudoPartition;     /* optional */
    std::optional<StandardPartition> standardPartition; /* optional */

  public:
    PortMappingType(PseudoPartition pseudoPart): pseudoPartition(std::move(pseudoPart)) {}

    PortMappingType(StandardPartition standardPart): standardPartition(std::move(standardPart)) {}
};

#endif
