#ifndef MULTIPARTITION_HM_TABLE
#define MULTIPARTITION_HM_TABLE

#include "multipartition_error_action.hpp"

class MultiPartitionHMTable {
private:
    MultiPartitionErrorAction multiPartitionErrorAction[1];
    std::vector<MultiPartitionErrorAction>* multiPartitionErrorActions =
        new (&multiPartitionErrorAction) std::vector<MultiPartitionErrorAction>;

    name_t tableName;                               /* required */
    std::vector<MultiPartitionErrorAction> errorActions; /* required */

public:
    MultiPartitionHMTable()
    {
    }

    MultiPartitionHMTable(name_t name, std::initializer_list<MultiPartitionErrorAction> actions)
        : tableName(name)
    {
        for (auto a : actions) {
            multiPartitionErrorActions->push_back(a);
        }
    }

    MultiPartitionHMTable(const MultiPartitionHMTable& rhs)
        : tableName(rhs.tableName)
    {
        for (auto a : rhs.getActions()) {
            multiPartitionErrorActions->push_back(a);
        }
    }

    MultiPartitionHMTable& operator=(const MultiPartitionHMTable&);

    const name_t& getTableName() const;

    const std::vector<MultiPartitionErrorAction>& getActions() const;
};

#endif
