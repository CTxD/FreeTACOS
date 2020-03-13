#ifndef PARTITION_HM_TABLE
#define PARTITION_HM_TABLE

#include "partition_error_action.hpp"

class PartitionHMTable {
private:
    PartitionErrorAction partitionErrorAction[1];
    std::vector<PartitionErrorAction>* partitionErrorActions =
        new (&partitionErrorAction) std::vector<PartitionErrorAction>;
    NAME_TYPE tableName;               /* required */
    NAME_TYPE multiPartitionTableName; /* required */

public:
    PartitionHMTable()
    {
    }

    PartitionHMTable(NAME_TYPE name,
                     NAME_TYPE multiPartitionHM,
                     std::initializer_list<PartitionErrorAction> actions)
        : tableName(name), multiPartitionTableName(multiPartitionHM)
    {
        for (auto a : actions) {
            partitionErrorActions->push_back(a);
        }
    }

    PartitionHMTable(const PartitionHMTable& rhs)
        : tableName(rhs.tableName), multiPartitionTableName(rhs.multiPartitionTableName)
    {
        for (auto a : rhs.getActions()) {
            partitionErrorActions->push_back(a);
        }
    }

    PartitionHMTable& operator=(const PartitionHMTable&);

    const NAME_TYPE& getTableName() const;

    const NAME_TYPE& getMultiPartitionTableName() const;

    const std::vector<PartitionErrorAction>& getActions() const;
};

#endif
