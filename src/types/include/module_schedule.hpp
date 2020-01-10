#ifndef MODULE_SCHEDULE
#define MODULE_SCHEDULE

#include "partition_schedule.hpp"

class ModuleSchedule {
private:
    PartitionSchedule majorFrameSecond[1];
    std::vector<PartitionSchedule>* majorFrameSeconds =
        new (&majorFrameSecond) std::vector<PartitionSchedule>;

public:
    ModuleSchedule(std::initializer_list<PartitionSchedule> majorFrame)
    {
        for (auto m : majorFrame) {
            majorFrameSeconds->push_back(m);
        }
    }

    const std::vector<PartitionSchedule>& getMajorFrameSeconds() const;
};

#endif
