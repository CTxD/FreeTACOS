#ifndef __CORE_SCHEDULE__
#define __CORE_SCHEDULE__

#include <partition_schedule.hpp>

#include <vector>

// Boost vector type
using namespace std;

// Define type aliases
typedef vector<PartitionSchedule> PartitionIterable;
typedef vector<vector<PartitionIterable>> CoreIterable;

class CoreSchedule {
private:
    CoreIterable cores;

public:
    CoreSchedule(CoreIterable cores) : cores(cores)
    {
    }
};

#endif
