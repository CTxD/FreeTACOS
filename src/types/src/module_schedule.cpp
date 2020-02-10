#include "module_schedule.hpp"

const std::vector<PartitionSchedule>& ModuleSchedule::getMajorFrameSeconds() const
{
  return *majorFrameSeconds;
}
