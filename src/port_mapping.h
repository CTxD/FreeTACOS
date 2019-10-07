#include "partition.h"

#ifndef PORT_MAPPING_TYPE
#define PORT_MAPPING_TYPE

class PortMappingType
{
  private:
    std::optional<PseudoPartition> pseudoPartition;     /* optional */
    std::optional<StandardPartition> standardPartition; /* optional */

  public:
    PortMappingType(PseudoPartition pseudoPart): pseudoPartition(pseudoPart) {}

    PortMappingType(StandardPartition standardPart): standardPart(standardPart) {}
};

#endif
