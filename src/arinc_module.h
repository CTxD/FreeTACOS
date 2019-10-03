#include "channel.h"
#include "schedule.h"
#include "general_types.h"
#include "module_hm_table.h"
#include "system_hm_table.h"
#include "partition_memory.h"
#include "partition_hm_table.h"

class Arinc
{
  private:
    std::optional<NameType> moduleName;                   /* optional */
    std::optional<NameType> moduleVersion;                /* optional */
    std::optional<IdentifierValueType> moduleID;          /* optional */
    Channel connectionTable[CHANNEL_NUMBER];              /* required */
    SystemHMTable systemHMTable;                          /* required */
    ModuleHMTable moduleHMTable;                          /* required */
    PartitionHMTable partitionHMTable[PARTITION_NUMBER];  /* required */
}
