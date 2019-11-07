#ifndef PORT_MAPPING
#define PORT_MAPPING

#include "pseudo_standard_partitions.h"
#include "general_types.h"


class PortMappingType
{
  private:
    std::optional<PseudoPartition> pseudoPartition;     /* optional */
    std::optional<StandardPartition> standardPartition; /* optional */

  public:
    PortMappingType() {};
    PortMappingType(PseudoPartition pseudoPart): pseudoPartition(std::move(pseudoPart)) {}

    PortMappingType(StandardPartition standardPart): standardPartition(std::move(standardPart)) {}

    PortMappingType(const PortMappingType& p): pseudoPartition(p.pseudoPartition),
      standardPartition(p.standardPartition) {}

    PortMappingType(PortMappingType&& p) noexcept: pseudoPartition(std::move(p.pseudoPartition)),
      standardPartition(std::move(p.standardPartition)) {}

    ~PortMappingType() = default;

};

#endif
