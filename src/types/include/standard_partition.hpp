#ifndef STANDARD_PARTITION
#define STANDARD_PARTITION

#include "pseudo_partition.hpp"

class StandardPartition : PseudoPartition {
private:
    identifier_t partitionIdentifier; /* required */
    NAME_TYPE portName;               /* required */

public:
    StandardPartition(identifier_t id,
                      NAME_TYPE partitionName,
                      NAME_TYPE portName,
                      APEX_INTEGER address,
                      NAME_TYPE procedure)
        : PseudoPartition(partitionName, address, procedure),
          partitionIdentifier(id),
          portName(portName)
    {
    }

    const identifier_t& getPartitionIdentifier() const;

    const NAME_TYPE& getPortName() const;
};

#endif
