#ifndef PARTITON_SCHEDULE
#define PARTITON_SCHEDULE

#include "general_types.h"


class PartitionSchedule
{
  private:
    bool partitionPeriodStart;        /* required */
    decOrHex_t periodDurationSeconds; /* required */
    name_t partitionName;             /* required */
    decOrHex_t offset;                /* required */

    identifier_t partitionIdentifier;

  public:
    PartitionSchedule(bool periodicStart, decOrHex_t duration, name_t partition, decOrHex_t offset):
      partitionPeriodStart(periodicStart), periodDurationSeconds(duration),
      partitionName(partition), offset(offset) {}

    bool getPartitionPeriodStart();

    decOrHex_t getPeriodDuration();

    name_t getPartitionName();

    decOrHex_t getOffset();

    void setPartitionIdentifier(identifier_t&& id);

    identifier_t getPartitionIdentifier();
};

#endif
