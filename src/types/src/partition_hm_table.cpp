#include "include/partition_hm_table.hpp"

PartitionHMTable& PartitionHMTable::operator=(const PartitionHMTable& rhs)
{
  tableName = rhs.tableName;
  multiPartitionTableName = rhs.multiPartitionTableName;
  actions = rhs.actions;
  return *this;
}

const name_t& PartitionHMTable::getTableName() const
{
  return tableName;
}

const name_t& PartitionHMTable::getMultiPartitionTableName() const
{
  return multiPartitionTableName;
}

const vector<PartitionErrorAction>& PartitionHMTable::getActions() const
{
  return actions;
}
