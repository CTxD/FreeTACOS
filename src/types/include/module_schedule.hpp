#ifndef MODULE_SCHEDULE
#define MODULE_SCHEDULE

#include "partition_schedule.hpp"

class ModuleSchedule {
private:
    PartitionSchedule partitionSchedule[100];
    MemoryArea partitionScheduleArea{std::data(partitionSchedule),
                                     std::size(partitionSchedule)};
    MonotonicMemoryResource<> partitionScheduleSrc{partitionScheduleArea};
    MonotonicAllocator<void> partitionSchedulerAllocator{partitionScheduleSrc};
    std::vector<PartitionSchedule, MonotonicAllocator<PartitionSchedule>> majorFrameSeconds{
        partitionSchedulerAllocator}; /* required */

public:
    ModuleSchedule(std::initializer_list<PartitionSchedule> majorFrame)
        : majorFrameSeconds(majorFrame)
    {
    }

    const std::vector<PartitionSchedule>& getMajorFrameSeconds() const;
};

#endif
