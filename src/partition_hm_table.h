#include "general_types.h"
#include "system_state_entry.h"

#ifndef PARTITION_HM_TABLE
#define PARTITION_HM_TABLE

class PartitionHMTable
{
  private:
    IdentifierValueType partitionIdentifier;    /* required */
    std::optional<NameType> partitionName;      /* optional */
    std::optional<NameType> partitionCallback;  /* optional */
    SystemStateEntry systemStates[MAX_NUMBER_SYSTEM_STATES]; /* required */
};

#endif
