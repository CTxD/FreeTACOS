#ifndef MODULE_SCHEDULE
#define MODULE_SCHEDULE

#include "partition_schedule.hpp"

class ModuleSchedule {
private:
    PartitionSchedule partitionSchedule[1];
    std::vector<PartitionSchedule>* partitionSchedules =
        new (&partitionSchedule) std::vector<PartitionSchedule>;
    std::vector<PartitionSchedule> majorFrameSeconds; /* required */

public:
    ModuleSchedule(std::initializer_list<PartitionSchedule> majorFrame)
    {
        for (auto m : majorFrame) {
            partitionSchedules->push_back(m);
        }
    }

    const std::vector<PartitionSchedule>& getMajorFrameSeconds() const;
};

#endif
