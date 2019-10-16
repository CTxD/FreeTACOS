#ifndef ARINC_MODULE
#define ARINC_MODULE

#include "channel.h"
#include "schedule.h"
#include "module_hm_table.h"
#include "system_hm_table.h"
#include "partition_memory.h"
#include "partition_hm_table.h"

class ArincModule
{
  private:
    std::optional<NameType> moduleName;                  /* optional */
    std::optional<NameType> moduleVersion;               /* optional */
    std::optional<IdentifierValueType> moduleID;         /* optional */
    Channel connectionTable;                             /* required */
    SystemHMTable systemHMTable;                         /* required */
    ModuleHMTable moduleHMTable;                         /* required */
    PartitionHMTable partitionHMTable;                   /* required */

  public:
    explicit ArincModule(const NameType name, const NameType version, const IdentifierValueType id,
                         Channel connections, SystemHMTable systemHM,
                         ModuleHMTable moduleHM, PartitionHMTable partitionHM):
      moduleName(std::move(name)), moduleVersion(std::move(version)), moduleID(std::move(id)),
      connectionTable(std::move(connections)), systemHMTable(std::move(systemHM)),
      moduleHMTable(std::move(moduleHM)), partitionHMTable(std::move(partitionHM)) {}
};

#endif
