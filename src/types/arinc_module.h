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


class ArincModule
{
  private:
    name_t moduleName;                    /* required */
    std::optional<name_t> moduleVersion;  /* optional */
    std::optional<APEX_INTEGER> moduleId; /* optional */

    Partition partitionBuffer[100];
    monotonic_buffer_resource partitionBufferSrc{std::data(partitionBuffer),
                                                  std::size(partitionBuffer)};

    SystemError systemErrorBuffer[100];
    monotonic_buffer_resource systemErrorBufferSrc{std::data(systemErrorBuffer),
                                                    std::size(systemErrorBuffer)};
    
    MultiPartitionHMTable multiPartitionHMTableBuffer[100];
    monotonic_buffer_resource multiPartitionHMTableBufferSrc{std::data(multiPartitionHMTableBuffer),
                                                              std::size(multiPartitionHMTableBuffer)};
  
    ModuleHMTable moduleHMTableBuffer[100];
    monotonic_buffer_resource moduleHMTableBufferSrc{std::data(moduleHMTableBuffer),
                                                      std::size(moduleHMTableBuffer)};

    PartitionHMTable partitionHMBuffer[125];
    monotonic_buffer_resource partitionHMBufferSrc{std::data(partitionHMBuffer),
                                                    std::size(partitionHMBuffer)};

    vector<Partition> partitions;                         /* required */
    ModuleSchedule schedule;                              /* required */
    vector<SystemError> errors;                           /* required */
    vector<MultiPartitionHMTable> multiPartitionHMTable;  /* required */
    vector<ModuleHMTable> moduleHMTable;                  /* required */
    vector<PartitionHMTable> partitionHMTable;            /* required */
    

  public:
    ArincModule() {};
    ArincModule(name_t name, std::optional<name_t> version, std::optional<identifier_t> id,
                std::initializer_list<Partition> part, std::initializer_list<PartitionSchedule> sched,
                std::initializer_list<SystemError> err,
                std::initializer_list<MultiPartitionHMTable> multiPartTab,
                std::initializer_list<ModuleHMTable> moduleHMTab,
                std::initializer_list<PartitionHMTable> partitionHMTab) :
                  moduleName(name), moduleVersion(version), moduleId(id),
                  partitions(part, &partitionBufferSrc), schedule(sched),
                  errors(err, &systemErrorBufferSrc),
                  multiPartitionHMTable(multiPartTab, &multiPartitionHMTableBufferSrc),
                  moduleHMTable(moduleHMTab, &moduleHMTableBufferSrc),
                  partitionHMTable(partitionHMTab, &partitionHMBufferSrc) {}

};

#endif
