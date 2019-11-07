#ifndef ARINC_MODULE
#define ARINC_MODULE

#include "channel.h"
#include "partition.h"
#include "system_error.h"
#include "module_schedule.h"
#include "module_hm_table.h"
#include "partition_memory.h"
#include "partition_hm_table.h"
#include "multipartition_hm_table.h"

#include <initializer_list>


class ArincModule
{
  private:
    name_t moduleName;                    /* required */
    std::optional<name_t> moduleVersion;  /* optional */
    std::optional<APEX_INTEGER> moduleId; /* optional */

    vector<SystemError> systemErrorsTable;
    vector<PartitionHMTable> partitionHMTable;    /* required */
    vector<Partition> partitions;                 /* required */

  public:
    ArincModule(name_t name, std::optional<name_t> version, std::optional<identifier_t> id,
                std::initializer_list<Partition> part, allocator_type alloc): //,
      moduleName(name), moduleVersion(version), moduleId(id), partitions(part, alloc) {}

    name_t getModuleName();

    name_t getModuleVersion();

    APEX_INTEGER getModuleId();

    vector<SystemError> getSystemErrorsTable();

    vector<PartitionHMTable> getPartitionHmTable();

    vector<Partition> getPartitions();

    ModuleSchedule getModuleSchedule();

    vector<MultiPartitionHMTable> getMultiPartitionHMTable();

    vector<ModuleHMTable> getModuleHmTable();

    vector<PartitionHMTable> getPartitionHMTable();
};

#endif
