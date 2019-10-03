#include "general_types.h"

class PseudoPartition {
  private:
    std::optional<NameType> name;                     /* optional */
    std::optional<DecOrHexValueType> physicalAdress;  /* optional */
    std::optional<NameType> procedure;                /* optional */
}

class StandardPartition {
  private:
    IdentifierValueType partitionIdentifier;  /* required */
    std::optional<NameType> partitionName;    /* optional */
    NameType portName;                        /* required */
    std::optional<int> physicalAdress;        /* optional */
}
