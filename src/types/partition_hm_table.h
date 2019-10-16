#include "general_types.h"
#include "system_state_entry.h"

#ifndef PARTITION_HM_TABLE
#define PARTITION_HM_TABLE

class PartitionHMTable
{
  private:
    IdentifierValueType partitionIdentifier;                  /* required */
    std::optional<nameType> partitionName;                    /* optional */
    std::optional<nameType> partitionCallback;                /* optional */
    SystemStateEntry systemStates[MAX_NUMBER_SYSTEM_STATES];  /* required */
};

#endif
