#ifndef ARINC_MODULE
#define ARINC_MODULE

#include <vector>

#include "channel.hpp"
#include "module_hm_table.hpp"
#include "module_schedule.hpp"
#include "multipartition_hm_table.hpp"
#include "partition.hpp"
#include "partition_hm_table.hpp"
#include "partition_memory.hpp"
#include "system_error.hpp"

class ArincModule {
private:
    NAME_TYPE moduleName;                   /* required */
    std::optional<NAME_TYPE> moduleVersion; /* optional */
    std::optional<APEX_INTEGER> moduleId;   /* optional */

    Partition partitionBuffer[100];
    MemoryArea partitionArea{std::data(partitionBuffer), std::size(partitionBuffer)};
    MonotonicMemoryResource<> partitionBufferSrc{partitionArea};
    MonotonicAllocator<Partition> partitionAlloc{partitionBufferSrc};

    SystemError systemErrorBuffer[100];
    MemoryArea sysErrorArea{std::data(systemErrorBuffer), std::size(systemErrorBuffer)};
    MonotonicMemoryResource<> systemErrorBufferSrc{sysErrorArea};
    MonotonicAllocator<SystemError> sysErrorAlloc{systemErrorBufferSrc};

    MultiPartitionHMTable multiPartitionHMTableBuffer[100];
    MemoryArea multiPartHMArea{std::data(multiPartitionHMTableBuffer),
                               std::size(multiPartitionHMTableBuffer)};
    MonotonicMemoryResource<> multiPartitionHMTableBufferSrc{multiPartHMArea};
    MonotonicAllocator<MultiPartitionHMTable> multiPartHMAlloc{multiPartitionHMTableBufferSrc};

    ModuleHMTable moduleHMTableBuffer[100];
    MemoryArea moduleHMArea{std::data(moduleHMTableBuffer), std::size(moduleHMTableBuffer)};
    MonotonicMemoryResource<> moduleHMTableBufferSrc{moduleHMArea};
    MonotonicAllocator<ModuleHMTable> moduleHMAllocator{moduleHMTableBufferSrc};

    PartitionHMTable partitionHMBuffer[125];
    MemoryArea partitionHMArea{std::data(partitionHMBuffer), std::size(partitionHMBuffer)};
    MonotonicMemoryResource<> partitionHMBufferSrc{partitionHMArea};
    MonotonicAllocator<PartitionHMTable> partitionHMAllocator{partitionHMBufferSrc};

    std::vector<Partition, MonotonicAllocator<Partition>> partitions{partitionAlloc}; /* required */
    std::vector<SystemError, MonotonicAllocator<SystemError>> systemErrorsTable{sysErrorAlloc}; /* required */
    std::vector<MultiPartitionHMTable, MonotonicAllocator<MultiPartitionHMTable>> multiPartitionHMTable{
        multiPartHMAlloc}; /* required */
    std::vector<ModuleHMTable, MonotonicAllocator<ModuleHMTable>> moduleHMTable{
        moduleHMAllocator}; /* required */
    std::vector<PartitionHMTable, MonotonicAllocator<PartitionHMTable>> partitionHMTable{
        partitionHMAllocator}; /* required */

public:
    ArincModule()
    {
    }

    ArincModule(NAME_TYPE name,
                std::optional<NAME_TYPE> version,
                std::optional<identifier_t> id,
                std::initializer_list<Partition> part,
                std::initializer_list<SystemError> err,
                std::initializer_list<MultiPartitionHMTable> multiPartTab,
                std::initializer_list<ModuleHMTable> moduleHMTab,
                std::initializer_list<PartitionHMTable> partitionHMTab)
        : moduleName(name),
          moduleVersion(version),
          moduleId(id),
          partitions(part),
          systemErrorsTable(err),
          multiPartitionHMTable(multiPartTab),
          moduleHMTable(moduleHMTab),
          partitionHMTable(partitionHMTab)
    {
    }

    const NAME_TYPE& getModuleName() const;

    const std::optional<NAME_TYPE>& getModuleVersion() const;

    const std::optional<APEX_INTEGER>& getModuleId() const;

    const std::vector<SystemError, MonotonicAllocator<SystemError>>& getSystemErrorsTable() const;

    const std::vector<PartitionHMTable, MonotonicAllocator<PartitionHMTable>>& getPartitionHmTable() const;

    const std::vector<Partition, MonotonicAllocator<Partition>>& getPartitions() const;

    const std::vector<MultiPartitionHMTable, MonotonicAllocator<MultiPartitionHMTable>>& getMultiPartitionHMTable() const;

    const std::vector<ModuleHMTable, MonotonicAllocator<ModuleHMTable>>& getModuleHmTable() const;

    const std::vector<PartitionHMTable, MonotonicAllocator<PartitionHMTable>>& getPartitionHMTable() const;
};

#endif
