#ifndef PSEUDO_PARTITION
#define PSEUDO_PARTITION

#include "general_types.hpp"


class PseudoPartition
{
  private:
    std::optional<name_t> name;                 /* optional */
    std::optional<decOrHex_t> physicalAddress;  /* optional */
    std::optional<name_t> procedure;            /* optional */

  public:
    PseudoPartition(name_t name, decOrHex_t address, name_t procedure):
      name(name), physicalAddress(address), procedure(procedure) {}

    const std::optional<name_t>& getName() const;

    const std::optional<decOrHex_t>& getPhysicalAddress() const;

    const std::optional<name_t>& getProcedure() const;
};

#endif
