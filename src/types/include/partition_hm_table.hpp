#ifndef PARTITION_HM_TABLE
#define PARTITION_HM_TABLE

#include "partition_error_action.hpp"

class PartitionHMTable {
private:
    PartitionErrorAction partitionErrorAction[100];
    MemoryArea PartitionErrorActionArea{std::data(partitionErrorAction),
                                        std::size(partitionErrorAction)};
    MonotonicMemoryResource<> partitionErrorActionSrc{PartitionErrorActionArea};
    MonotonicAllocator<void> partitionErrorActionAllocator{partitionErrorActionSrc};
    NAME_TYPE tableName;               /* required */
    NAME_TYPE multiPartitionTableName; /* required */
    std::vector<PartitionErrorAction, MonotonicAllocator<PartitionErrorAction>> actions{
        partitionErrorActionAllocator}; /* required */

public:
    PartitionHMTable()
    {
    }

    PartitionHMTable(NAME_TYPE name,
                     NAME_TYPE multiPartitionHM,
                     std::initializer_list<PartitionErrorAction> actions)
        : tableName(name), multiPartitionTableName(multiPartitionHM), actions(actions)
    {
    }

    PartitionHMTable(const PartitionHMTable& rhs)
        : tableName(rhs.tableName),
          multiPartitionTableName(rhs.multiPartitionTableName),
          actions(rhs.actions)
    {
    }

    PartitionHMTable& operator=(const PartitionHMTable&);

    const NAME_TYPE& getTableName() const;

    const NAME_TYPE& getMultiPartitionTableName() const;

    const std::vector<PartitionErrorAction>& getActions() const;
};

#endif
