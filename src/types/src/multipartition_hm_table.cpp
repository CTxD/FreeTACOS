#include "multipartition_hm_table.hpp"

MultiPartitionHMTable& MultiPartitionHMTable::operator=(const MultiPartitionHMTable& rhs)
{
    tableName = rhs.tableName;
    errorActions = rhs.errorActions;
    return *this;
}

const NAME_TYPE& MultiPartitionHMTable::getTableName() const
{
    return tableName;
}

const std::vector<MultiPartitionErrorAction>& MultiPartitionHMTable::getActions() const
{
    return errorActions;
}
