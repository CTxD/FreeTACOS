#include <core_schedule.hpp>

const CoreIterable& CoreSchedule::getCores() const
{
    return *coreIterable;
};

const PartitionIterable& CoreSchedule::getPartitions(unsigned core) const
{
    return (*coreIterable)[core];
};