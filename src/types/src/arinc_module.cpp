#include "include/arinc_module.hpp"

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

const vector<SystemError>& ArincModule::getSystemErrorsTable() const
{
  return systemErrorsTable;
};

const vector<PartitionHMTable>& ArincModule::getPartitionHmTable() const
{
  return partitionHMTable;
};

const vector<Partition>& ArincModule::getPartitions() const
{
  return partitions;
};

const ModuleSchedule& ArincModule::getModuleSchedule() const
{
  return schedule;
};

const vector<MultiPartitionHMTable>& ArincModule::getMultiPartitionHMTable() const
{
  return multiPartitionHMTable;
};

const vector<ModuleHMTable>& ArincModule::getModuleHmTable() const
{
  return moduleHMTable;
};

const vector<PartitionHMTable>& ArincModule::getPartitionHMTable() const
{
  return partitionHMTable;
};
