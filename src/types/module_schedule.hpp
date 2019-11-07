#ifndef MODULE_SCHEDULE
#define MODULE_SCHEDULE

#include "partition_schedule.h"


class ModuleSchedule
{
  private:
    vector<PartitionSchedule> majorFrameSeconds;   /* required */

  public:
    ModuleSchedule(vector<PartitionSchedule> majorFrame): majorFrameSeconds(majorFrame) {}

    vector<PartitionSchedule> getMajorFrameSeconds();
};

#endif
