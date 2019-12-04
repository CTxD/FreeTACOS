#ifndef PSEUDO_PARTITION
#define PSEUDO_PARTITION

#include "general_types.hpp"


class PseudoPartition
{
  private:
    std::optional<NAME_TYPE> name;                 /* optional */
    std::optional<decOrHex_t> physicalAddress;  /* optional */
    std::optional<NAME_TYPE> procedure;            /* optional */

  public:
    PseudoPartition(NAME_TYPE name, decOrHex_t address, NAME_TYPE procedure):
      name(name), physicalAddress(address), procedure(procedure) {}

    const std::optional<NAME_TYPE>& getName() const;

    const std::optional<decOrHex_t>& getPhysicalAddress() const;

    const std::optional<NAME_TYPE>& getProcedure() const;
};

#endif
