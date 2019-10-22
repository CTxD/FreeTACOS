#ifndef SCHEDULE
#define SCHEDULE

#include "general_types.h"


class WindowSchedule
{
  private:
    identifier_t windowIdentifier;  /* required */
    float windowStartSeconds;       /* required */
    float windowDurationSeconds;    /* required */
    bool partitionPeriodStart;      /* required */

  public:
    WindowSchedule(identifier_t id, float startSec, float durationSec, bool periodStart):
      windowIdentifier(id), windowStartSeconds(startSec),
      windowDurationSeconds(durationSec), partitionPeriodStart(periodStart) {}

    WindowSchedule(const WindowSchedule& w): windowIdentifier(w.windowIdentifier),
      windowStartSeconds(w.windowStartSeconds), windowDurationSeconds(w.windowDurationSeconds),
      partitionPeriodStart(w.partitionPeriodStart) {}

    WindowSchedule(WindowSchedule&& w) noexcept: windowIdentifier(std::move(w.windowIdentifier)),
      windowStartSeconds(std::move(w.windowStartSeconds)),
      windowDurationSeconds(std::move(w.windowDurationSeconds)),
      partitionPeriodStart(std::move(w.partitionPeriodStart)) {}

    ~WindowSchedule() = default;

};

class PartitionSchedule
{
  private:
    bool partitionPeriodStart;        /* required */
    decOrHex_t periodDurationSeconds; /* required */
    name_t partitionName;             /* required */
    decOrHex_t offset;                /* required */

    // Deprecated
    identifier_t partitionIdentifier;      /* required */
    float periodSeconds;                   /* required */
    std::vector<WindowSchedule> windows;   /* required */

  public:
    PartitionSchedule(bool periodicStart, decOrHex_t duration, name_t partition, decOrHex_t offset):
      partitionPeriodStart(periodicStart), periodDurationSeconds(duration),
      partitionName(partition), offset(offset) {}
};

class ModuleSchedule
{
  private:
    std::vector<PartitionSchedule> majorFrameSeconds;   /* required */

  public:
    ModuleSchedule(std::vector<PartitionSchedule> majorFrame): majorFrameSeconds(majorFrame) {}
};

#endif
