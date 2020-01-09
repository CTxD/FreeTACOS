#ifndef __CORE_SCHEDULE__
#define __CORE_SCHEDULE__

#include <partition_schedule.hpp>
#include <vector>

// Define type aliases
typedef std::vector<PartitionSchedule> PartitionIterable;
typedef std::vector<std::vector<PartitionIterable>> CoreIterable;

class CoreSchedule {
private:
    CoreIterable cores;

public:
    CoreSchedule(CoreIterable cores) : cores(cores)
    {
    }
};

#endif
