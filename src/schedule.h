#include "general_types.h"

#ifndef SCHEDULE
#define SCHEDULE

class WindowSchedule
{
  private:
    IdentifierValueType windowIdentifier; /* required */
    float windowStartSeconds;             /* required */
    float windowDurationSeconds;          /* required */
    bool partitionPeriodStart;            /* required */

  public:
    WindowSchedule(IdentifierValueType id, float startSec, float durationSec, bool periodStart):
      windowIdentifier(id), windowStartSeconds(startSec), windowDurationSeconds(durationSec), partitionPeriodStart(periodStart) {}
};

class PartitionSchedule
{
  private:
    IdentifierValueType partitionIdentifier;    /* required */
    std::optional<NameType> partitionName;      /* optional */
    float periodSeconds;                        /* required */
    float periodDurationSeconds;                /* required */
    WindowSchedule* windows;                    /* required */

  public:
    PartitionSchedule(IdentifierValueType id, NameType name, float periodSec, float durationSec, WindowSchedule* windows):
      partitionIdentifier(id), partitionName(name), periodSeconds(periodSec), periodDurationSeconds(durationSec), windows(windows) {}
};

class ModuleSchedule
{
  private:
    PartitionSchedule* majorFrameSeconds;   /* required */

  public:
    ModuleSchedule(PartitionSchedule* majorFrame): majorFrameSeconds(majorFrame) {}
};

#endif
