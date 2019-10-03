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
};

class PartitionSchedule
{
  private:
    IdentifierValueType partitionIdentifier;    /* required */
    std::optional<NameType> partitionName;      /* optional */
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
