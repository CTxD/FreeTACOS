#include "partition_schedule.hpp"

const bool& PartitionSchedule::getPartitionPeriodStart() const
{
    return partitionPeriodStart;
}

const decOrHex_t& PartitionSchedule::getDuration() const
{
    return periodDurationSeconds;
}

const NAME_TYPE& PartitionSchedule::getPartitionName() const
{
    return partitionName;
}

const decOrHex_t& PartitionSchedule::getOffset() const
{
    return offset;
}

void PartitionSchedule::setPartitionIdentifier(identifier_t id)
{
    partitionIdentifier = std::move(id);
}

const identifier_t& PartitionSchedule::getPartitionIdentifier() const
{
    return partitionIdentifier;
}

const PROCESSOR_CORE_ID_TYPE& PartitionSchedule::getCoreAffinity() const
{
    return affinity;
}
