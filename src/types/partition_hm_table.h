#ifndef PARTITION_HM_TABLE
#define PARTITION_HM_TABLE

#include "system_state_entry.h"

class PartitionHMTable
{
  private:
    IdentifierValueType partitionIdentifier;    /* required */
    std::optional<NameType> partitionName;      /* optional */
    std::optional<NameType> partitionCallback;  /* optional */
    SystemStateEntry* systemStates;             /* required */

  public:
    PartitionHMTable(IdentifierValueType id, NameType name, NameType callback, SystemStateEntry* entry):
      partitionIdentifier(id), partitionName(name), partitionCallback(callback), systemStates(entry) {}
};

#endif
