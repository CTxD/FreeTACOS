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
    std::optional<NameType> moduleName;                   /* optional */
    std::optional<NameType> moduleVersion;                /* optional */
    std::optional<IdentifierValueType> moduleID;          /* optional */
    Channel* connectionTable;                             /* required */
    SystemHMTable* systemHMTable;                         /* required */
    ModuleHMTable* moduleHMTable;                         /* required */
    PartitionHMTable* partitionHMTable;                   /* required */

  public:
    ArincModule(NameType name, NameType version, IdentifierValueType id, Channel* connecions,
                SystemHMTable systemHM, ModuleHMTable moduleHM, PartitionHMTable partitionHM):
                moduleName(name), moduleVersion(version), moduleID(id), connectionTable(connecions),
                systemHMTable(systemHM), moduleHMTable(moduleHM), partitionHMTable(partitionHM) {}
};

#endif
