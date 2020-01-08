#ifndef PARTITION_HM_TABLE
#define PARTITION_HM_TABLE

#include "partition_error_action.hpp"

class PartitionHMTable {
private:
    PartitionErrorAction partitionErrorAction[100];
    std::vector<PartitionErrorAction>* partitionErrorActions =
        new (&partitionErrorAction) std::vector<PartitionErrorAction>;
    name_t tableName;                     /* required */
    name_t multiPartitionTableName;       /* required */
    vector<PartitionErrorAction> actions; /* required */

public:
    PartitionHMTable()
    {
    }

    PartitionHMTable(name_t name,
                     name_t multiPartitionHM,
                     std::initializer_list<PartitionErrorAction> actions)
        : tableName(name), multiPartitionTableName(multiPartitionHM)
    {
        for (auto a : actions) {
            partitionErrorActions->push_back(a);
        }
    }

    PartitionHMTable(const PartitionHMTable& rhs)
        : tableName(rhs.tableName),
          multiPartitionTableName(rhs.multiPartitionTableName),
          actions(rhs.actions)
    {
        for (auto a : rhs.getActions()) {
            partitionErrorActions->push_back(a);
        }
    }

    PartitionHMTable& operator=(const PartitionHMTable&);

    const name_t& getTableName() const;

    const name_t& getMultiPartitionTableName() const;

    const vector<PartitionErrorAction>& getActions() const;
};

#endif
