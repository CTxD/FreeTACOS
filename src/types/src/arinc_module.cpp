#include "arinc_module.hpp"

const name_t& ArincModule::getModuleName() const
{
  return moduleName;
};

const std::optional<name_t>& ArincModule::getModuleVersion() const
{
  return moduleVersion;
};

const std::optional<APEX_INTEGER>& ArincModule::getModuleId() const
{
  return moduleId;
};

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
