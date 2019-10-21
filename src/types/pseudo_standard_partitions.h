#ifndef OTHER_PARTITIONS
#define OTHER_PARTITIONS

#include "general_types.h"

// Deprecated
class PseudoPartition
{
  private:
    std::optional<name_t> name;                 /* optional */
    std::optional<decOrHex_t> physicalAddress;  /* optional */
    std::optional<name_t> procedure;            /* optional */

  public:
    PseudoPartition(name_t name, decOrHex_t address, name_t procedure):
      name(name), physicalAddress(address), procedure(procedure) {}

    PseudoPartition(const PseudoPartition& p):
    name(p.name), physicalAddress(p.physicalAddress), procedure(p.procedure) {}

    PseudoPartition(PseudoPartition&& p) noexcept :
      name(std::move(p.name)), physicalAddress(std::move(p.physicalAddress)), procedure(std::move(p.procedure)) {}

    ~PseudoPartition() = default;
};

class StandardPartition
{
  private:
    identifier_t partitionIdentifier;     /* required */
    std::optional<name_t> partitionName;  /* optional */
    name_t portName;                      /* required */
    std::optional<int> physicalAddress;   /* optional */

  public:
    StandardPartition(identifier_t id, name_t partitionName, name_t portName, int address):
      partitionIdentifier(id), partitionName(partitionName), portName(portName), physicalAddress(address) {}

    StandardPartition(const StandardPartition& s):
      partitionIdentifier(s.partitionIdentifier), partitionName(s.partitionName),
      portName(s.portName), physicalAddress(s.physicalAddress) {}

    StandardPartition(StandardPartition&& s) noexcept:
      partitionIdentifier(std::move(s.partitionIdentifier)), partitionName(std::move(s.partitionName)),
      portName(std::move(s.portName)), physicalAddress(std::move(s.physicalAddress)) {}

    ~StandardPartition() = default;
};

#endif
