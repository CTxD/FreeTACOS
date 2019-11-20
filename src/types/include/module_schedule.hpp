#ifndef MODULE_SCHEDULE
#define MODULE_SCHEDULE

#include "partition_schedule.hpp"


class ModuleSchedule
{
  private:
    PartitionSchedule partitionSchedule[100];
    monotonic_buffer_resource partitionScheduleSrc{std::data(partitionSchedule),
                                                   std::size(partitionSchedule)};
    vector<PartitionSchedule> majorFrameSeconds;   /* required */

  public:
    ModuleSchedule() {};

    ModuleSchedule(std::initializer_list<PartitionSchedule> majorFrame):
      majorFrameSeconds(majorFrame, &partitionScheduleSrc) {}

    const vector<PartitionSchedule>& getMajorFrameSeconds() const;
};

#endif
