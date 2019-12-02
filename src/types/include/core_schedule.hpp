#ifndef __CORE_SCHEDULE__
#define __CORE_SCHEDULE__

#include <partition_schedule.hpp>

#include <boost/container/pmr/vector.hpp>

// Boost vector type
using namespace boost::container::pmr;

// Define type aliases
typedef vector<PartitionSchedule> PartitionIterable;
typedef vector<PartitionIterable> CoreIterable;

class CoreSchedule {
private:
    CoreIterable cores;

public:
    CoreSchedule(CoreIterable cores) : cores(cores)
    {
    }
};

#endif
