#include "channel.h"
#include "schedule.h"
#include "general_types.h"
#include "module_hm_table.h"
#include "system_hm_table.h"
#include "partition_memory.h"
#include "partition_hm_table.h"

#ifndef ARINC_MODULE
#define ARINC_MODULE

class ArincModule
{
  private:
    std::optional<nameType> moduleName;                   /* optional */
    std::optional<nameType> moduleVersion;                /* optional */
    std::optional<identifierValueType> moduleID;          /* optional */
    Channel connectionTable[CHANNEL_NUMBER];              /* required */
    SystemHMTable systemHMTable;                          /* required */
    ModuleHMTable moduleHMTable;                          /* required */
    PartitionHMTable partitionHMTable[PARTITION_NUMBER];  /* required */
}

#endif
