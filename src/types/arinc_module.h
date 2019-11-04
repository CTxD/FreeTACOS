#ifndef ARINC_MODULE
#define ARINC_MODULE

#include "channel.h"
#include "schedule.h"
#include "partition.h"
#include "module_hm_table.h"
#include "partition_memory.h"
#include "system_state_entry.h"
#include "partition_hm_table.h"
#include "multipartition_hm_table.h"

#include <initializer_list>

#include <boost/container/pmr/vector.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>
#include <boost/container/pmr/monotonic_buffer_resource.hpp>


using namespace boost::container::pmr;

typedef memory_resource* allocator_type;

class ArincModule
{
  private:
    name_t moduleName;                    /* required */
    std::optional<name_t> moduleVersion;  /* optional */
    std::optional<APEX_INTEGER> moduleId; /* optional */

    vector<SystemError> errors;
    vector<MultiPartitionHMTable> multiPartitionHMTable{&multiPartHMMemory}; /* required */
    vector<ModuleHMTable> moduleHMTable{&moduleHMMemory};                    /* required */
    vector<PartitionHMTable> partitionHMTable{&partitionHMMemory};           /* required */
    vector<Partition> partitions;                                            /* required */

    // ModuleSchedule schedule;                    /* required */
    // std::optional<QueuingPort> queuingPorts;    /* required */
    // std::optional<SamplingPort> samplingPorts;  /* required */

  public:
    ArincModule(name_t name, std::optional<name_t> version, std::optional<identifier_t> id,
                std::initializer_list<Partition> part, allocator_type alloc): //,
      moduleName(name), moduleVersion(version), moduleId(id),
                         // , ModuleSchedule schedule,
                         // std::vector<ArincModule> err, std::vector<MultiPartitionHMTable> multiPartitionHM,
                         // std::vector<ModuleHMTable> moduleHM, std::vector<PartitionHMTable> partitionHM):
      partitions(part, alloc) {}
      // , schedule(schedule), errors(err.begin(), err.end()),
      // multiPartitionHMTable(multiPartitionHM.begin(), multiPartitionHM.end()),
      // moduleHMTable(moduleHM.begin(), moduleHM.end()), partitionHMTable(partitionHM.begin(), partitionHM.end()) {}
};

#endif
