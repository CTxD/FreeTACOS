#ifndef __CORE_SCHEDULE__
#define __CORE_SCHEDULE__

#include "partition_schedule.hpp"

// Define type aliases
typedef std::vector<PartitionSchedule, MonotonicAllocator<PartitionSchedule>> PartitionIterable;
typedef std::vector<std::vector<PartitionIterable, MonotonicAllocator<PartitionIterable>>> CoreIterable;

class CoreSchedule {
private:
    CoreIterable cores;

public:
    CoreSchedule(CoreIterable cores) : cores(cores)
    {
    }
};

#endif
