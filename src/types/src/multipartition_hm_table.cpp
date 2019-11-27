#include "include/multipartition_hm_table.hpp"

MultiPartitionHMTable& MultiPartitionHMTable::operator=(const MultiPartitionHMTable& rhs) {
  tableName = rhs.tableName;
  errorActions = rhs.errorActions;
  return *this;
}

const name_t& MultiPartitionHMTable::getTableName() const
{
  return tableName;
}

const vector<MultiPartitionErrorAction>& MultiPartitionHMTable::getActions() const
{
  return errorActions;
}
