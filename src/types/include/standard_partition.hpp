#ifndef STANDARD_PARTITION
#define STANDARD_PARTITION

#include "pseudo_partition.hpp"


class StandardPartition : PseudoPartition
{
  private:
    identifier_t partitionIdentifier;     /* required */
    name_t portName;                      /* required */

  public:
    StandardPartition(identifier_t id, name_t partitionName, name_t portName,APEX_INTEGER address, name_t procedure):
      PseudoPartition(partitionName, address, procedure), partitionIdentifier(id), portName(portName) {}

    const identifier_t& getPartitionIdentifier() const;

    const name_t& getPortName() const;
};

#endif
