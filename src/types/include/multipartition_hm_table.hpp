#ifndef MULTIPARTITION_HM_TABLE
#define MULTIPARTITION_HM_TABLE

#include "multipartition_error_action.hpp"

class MultiPartitionHMTable {
private:
    MultiPartitionErrorAction multiPartitionErrorAction[100];
    MemoryArea multiPartErrorArea{std::data(multiPartitionErrorAction),
                                  std::size(multiPartitionErrorAction)};
    MonotonicMemoryResource<> multiPartitionErrorActionSrc{multiPartErrorArea};
    MonotonicAllocator<void> multiPartitionErrorAllocator{multiPartitionErrorActionSrc};

    NAME_TYPE tableName; /* required */
    std::vector<MultiPartitionErrorAction, MonotonicAllocator<MultiPartitionErrorAction>> errorActions{
        multiPartitionErrorAllocator}; /* required */

public:
    MultiPartitionHMTable()
    {
    }

    MultiPartitionHMTable(NAME_TYPE name, std::initializer_list<MultiPartitionErrorAction> actions)
        : tableName(name), errorActions(actions)
    {
    }

    MultiPartitionHMTable(const MultiPartitionHMTable& rhs)
        : tableName(rhs.tableName), errorActions(rhs.errorActions)
    {
    }

    MultiPartitionHMTable& operator=(const MultiPartitionHMTable&);

    const NAME_TYPE& getTableName() const;

    const std::vector<MultiPartitionErrorAction>& getActions() const;
};

#endif
