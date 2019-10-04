#include "general_types.h"

#ifndef SCHEDULE
#define SCHEDULE

class WindowSchedule
{
  private:
    identifierValueType windowIdentifier; /* required */
    float windowStartSeconds;             /* required */
    float windowDurationSeconds;          /* required */
    bool partitionPeriodStart;            /* required */
};

class PartitionSchedule
{
  private:
    identifierValueType partitionIdentifier;    /* required */
    std::optional<nameType> partitionName;      /* optional */
    float periodSeconds;                        /* required */
    float periodDurationSeconds;                /* required */
    WindowSchedule windows[MAX_NUMBER_WINDOWS]; /* required */
};

class ModuleSchedule
{
  private:
    PartitionSchedule majorFrameSeconds[WINDOW_NUMBER]; /* required */
};

#endif
