#ifndef ARINC_MODULE
#define ARINC_MODULE

#include <vector>

#include "channel.h"
#include "schedule.h"
#include "partition.h"
#include "alocator.h"
#include "module_hm_table.h"
#include "partition_memory.h"
#include "system_state_entry.h"
#include "partition_hm_table.h"
#include "multipartition_hm_table.h"

class ArincModule
{
  private:
    name_t moduleName;                    /* required */
    std::optional<name_t> moduleVersion;  /* optional */
    std::optional<identifier_t> moduleId; /* optional */

    std::vector<SystemError> errors;
    std::vector<MultiPartitionHMTable> multiPartitionHMTable; /* required */
    std::vector<ModuleHMTable> moduleHMTable;                 /* required */
    std::vector<PartitionHMTable> partitionHMTable;           /* required */

    MemoryArea partitionArea{GIGABYTE};
    MonotonicResource<> memory{partitionArea};
    MonotonicAllocator<void> alocator{memory};

    std::vector<Partition> partitions;          /* required */
    ModuleSchedule schedule;                    /* required */
    std::optional<QueuingPort> queuingPorts;    /* required */
    std::optional<SamplingPort> samplingPorts;  /* required */

  public:
    explicit ArincModule(name_t name, name_t version, identifier_t id,
                         std::vector<Partition> part, ModuleSchedule schedule,
                         std::vector<SystemError> err, std::vector<MultiPartitionHMTable> multiPartitionHM,
                         std::vector<ModuleHMTable> moduleHM, std::vector<PartitionHMTable> partitionHM):
      moduleName(std::move(name)), moduleVersion(std::move(version)), moduleId(std::move(id)),
      partitions(std::move(part)), schedule(schedule), errors(err),multiPartitionHMTable(std::move(multiPartitionHM)),
      moduleHMTable(std::move(moduleHM)), partitionHMTable(std::move(partitionHM)) {}
};

#endif
