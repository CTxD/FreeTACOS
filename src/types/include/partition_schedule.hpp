#ifndef PARTITON_SCHEDULE
#define PARTITON_SCHEDULE

#include <apex_types.hpp>
#include <general_types.hpp>

class PartitionSchedule {
private:
    bool partitionPeriodStart;        /* required */
    decOrHex_t periodDurationSeconds; /* required */
    NAME_TYPE partitionName;          /* required */
    decOrHex_t offset;                /* required */
    decOrHex_t period;                /* required */
    PROCESSOR_CORE_ID_TYPE affinity;  /* required */

    identifier_t partitionIdentifier;

public:
    PartitionSchedule()
    {
    }

    PartitionSchedule(bool periodicStart,
                      decOrHex_t duration,
                      NAME_TYPE name,
                      decOrHex_t offset,
                      decOrHex_t period,
                      PROCESSOR_CORE_ID_TYPE affinity)
        : partitionPeriodStart(periodicStart),
          periodDurationSeconds(duration),
          partitionName(name),
          offset(offset),
          period(period),
          affinity(affinity)
    {
    }

    const bool& getPartitionPeriodStart() const;

    const decOrHex_t& getDuration() const;

    const NAME_TYPE& getPartitionName() const;

    const decOrHex_t& getOffset() const;

    void setPartitionIdentifier(identifier_t id);

    const identifier_t& getPartitionIdentifier() const;

    const PROCESSOR_CORE_ID_TYPE& getCoreAffinity() const;
};

#endif
