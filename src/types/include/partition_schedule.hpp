#ifndef PARTITON_SCHEDULE
#define PARTITON_SCHEDULE

#include "general_types.hpp"


class PartitionSchedule
{
  private:
    bool partitionPeriodStart;        /* required */
    decOrHex_t periodDurationSeconds; /* required */
    name_t partitionName;             /* required */
    decOrHex_t offset;                /* required */

    identifier_t partitionIdentifier;

  public:
    PartitionSchedule() {}

    PartitionSchedule(bool periodicStart, decOrHex_t duration, name_t partition, decOrHex_t offset):
      partitionPeriodStart(periodicStart), periodDurationSeconds(duration),
      partitionName(partition), offset(offset) {}

    const bool& getPartitionPeriodStart() const;

    const decOrHex_t& getPeriodDuration() const;

    const name_t& getPartitionName() const;

    const decOrHex_t& getOffset() const;

    void setPartitionIdentifier(identifier_t id);

    const identifier_t& getPartitionIdentifier() const;
};

#endif
