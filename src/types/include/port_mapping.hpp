#ifndef PORT_MAPPING
#define PORT_MAPPING

#include "pseudo_partition.hpp"
#include "standard_partition.hpp"

class PortMapping {
private:
    std::optional<PseudoPartition> pseudoPartition;     /* optional */
    std::optional<StandardPartition> standardPartition; /* optional */

public:
    PortMapping(){};

    PortMapping(PseudoPartition pseudoPart)
        : pseudoPartition(std::move(pseudoPart))
    {
    }

    PortMapping(StandardPartition standardPart)
        : standardPartition(std::move(standardPart))
    {
    }

    const std::optional<PseudoPartition>& getPseudoPartition() const;

    const std::optional<StandardPartition>& getStandardPartition() const;
};

#endif
