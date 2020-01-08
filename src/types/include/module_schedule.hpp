#ifndef MODULE_SCHEDULE
#define MODULE_SCHEDULE

#include "partition_schedule.hpp"

class ModuleSchedule {
private:
    PartitionSchedule partitionSchedule[100];
    std::vector<PartitionSchedule>* partitionSchedules =
        new (&partitionSchedule) std::vector<PartitionSchedule>;
    vector<PartitionSchedule> majorFrameSeconds; /* required */

public:
    ModuleSchedule(std::initializer_list<PartitionSchedule> majorFrame)
    {
        for (auto m : majorFrame) {
            partitionSchedules->push_back(m);
        }
    }

    const vector<PartitionSchedule>& getMajorFrameSeconds() const;
};

#endif
