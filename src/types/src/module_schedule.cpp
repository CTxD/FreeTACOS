#include "include/module_schedule.hpp"

const std::vector<PartitionSchedule, MonotonicAllocator<PartitionSchedule>>& ModuleSchedule::getMajorFrameSeconds() const
{
    return majorFrameSeconds;
}
