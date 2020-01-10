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

const std::vector<SystemError>& ArincModule::getSystemErrorsTable() const
{
    return *systemErrors;
};

const std::vector<PartitionHMTable>& ArincModule::getPartitionHMTable() const
{
    return *partitionHMTables;
};

const std::vector<Partition>& ArincModule::getPartitions() const
{
    return *partitions;
};

const std::vector<MultiPartitionHMTable>& ArincModule::getMultiPartitionHMTable() const
{
    return *multiPartitionHMTables;
};

const std::vector<ModuleHMTable>& ArincModule::getModuleHmTable() const
{
    return *moduleHMTables;
};
