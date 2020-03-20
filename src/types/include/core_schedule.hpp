#ifndef __CORE_SCHEDULE__
#define __CORE_SCHEDULE__

#include <partition_schedule.hpp>
#include <vector>

// Define type aliases
typedef std::vector<PartitionSchedule> PartitionIterable;
typedef std::vector<PartitionIterable> CoreIterable;

class CoreSchedule {
private:
    PartitionSchedule partitionIterable[4][30];
    CoreIterable* coreIterable = new (&partitionIterable) CoreIterable;

public:
    CoreSchedule(std::initializer_list<std::initializer_list<PartitionSchedule>> coreIter)
    {
        for (auto core : coreIter) {
            coreIterable->push_back(core);
        }
    }

    const CoreIterable& getCores() const;

    const PartitionIterable& getPartitions(unsigned core) const;
};

#endif
