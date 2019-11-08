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

    name_t getName();

    decOrHex_t getPhysicalAddress();

    name_t getProcedure();
};

#endif
