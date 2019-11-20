#ifndef PARTITON_SCHEDULE
#define PARTITON_SCHEDULE

#include "general_types.hpp"

class PartitionSchedule {
private:
    bool partitionPeriodStart;        /* required */
    decOrHex_t periodDurationSeconds; /* required */
    name_t partitionName;             /* required */
    decOrHex_t offset;                /* required */

    decOrHex_t period;
    PROCESSOR_CORE_ID_TYPE affinity;

public:
    PartitionSchedule()
    {
    }

    PartitionSchedule(name_t partition,
                      PROCESSOR_CORE_ID_TYPE affinity,
                      decOrHex_t duration,
                      decOrHex_t period,
                      decOrHex_t offset,
                      bool periodicStart)
        : partitionName(partition),
          affinity(affinity),
          periodDurationSeconds(duration),
          period(period),
          offset(offset),
          partitionPeriodStart(periodicStart)
    {
    }

    const bool& getPartitionPeriodStart() const;

    const decOrHex_t& getPeriodDuration() const;

    const name_t& getPartitionName() const;

    const decOrHex_t& getOffset() const;

    const decOrHex_t& getPeriod() const;

    const PROCESSOR_CORE_ID_TYPE& getAffinity() const;
};

#endif
