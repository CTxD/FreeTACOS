#include "include/arinc_module.hpp"

const NAME_TYPE& ArincModule::getModuleName() const
{
    return moduleName;
}

const std::optional<NAME_TYPE>& ArincModule::getModuleVersion() const
{
    return moduleVersion;
}

const std::optional<APEX_INTEGER>& ArincModule::getModuleId() const
{
    return moduleId;
}

const std::vector<SystemError, MonotonicAllocator<SystemError>>& ArincModule::getSystemErrorsTable() const
{
    return systemErrorsTable;
}

const std::vector<PartitionHMTable, MonotonicAllocator<PartitionHMTable>>& ArincModule::getPartitionHmTable() const
{
    return partitionHMTable;
}

const std::vector<Partition, MonotonicAllocator<Partition>>& ArincModule::getPartitions() const
{
    return partitions;
}

const std::vector<MultiPartitionHMTable, MonotonicAllocator<MultiPartitionHMTable>>& ArincModule::getMultiPartitionHMTable() const
{
    return multiPartitionHMTable;
}

const std::vector<ModuleHMTable, MonotonicAllocator<ModuleHMTable>>& ArincModule::getModuleHmTable() const
{
    return moduleHMTable;
}

const std::vector<PartitionHMTable, MonotonicAllocator<PartitionHMTable>>& ArincModule::getPartitionHMTable() const
{
    return partitionHMTable;
}
