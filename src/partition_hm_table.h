#include "general_types.h"
#include "system_state_entry.h"

public class PartitionHMTable
{
  private:
    IdentifierValueType partitionIdentifier;    /* required */
    std::optional<NameType> partitionName;      /* optional */
    std::optional<NameType> partitionCallback;  /* optional */
    SystemStateEntry systemStates[MAX_NUMBER_SYSTEM_STATES]; /* required */
}
