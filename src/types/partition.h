#ifndef PARTITION_H
#define PARTITION_H

#include "process.h"
#include "port_type.h"
#include "apex_types.h"
#include "apex_error.h"
#include "apex_partition.h"
#include "memory_requirements.h"


class Partition
{
    private:
        identifier_t partitionIdentifier;       /* required */
        PROCESSOR_CORE_ID_TYPE affinity = CORE_AFFINITY_NO_PREFERENCE;
        name_t partitionName;                   /* required */

        decOrHex_t duration;                    /* required */
        decOrHex_t period;                      /* required */

        std::vector<MemoryRegion> memoryRegions;/* required */
        std::vector<QueuingPort> queuePorts;    /* required */
        std::vector<SamplingPort> samplePorts;  /* required */

        OPERATING_MODE_TYPE mode;
        PARTITION_STATUS_TYPE status;

        std::optional<std::vector<Process>> process;

        // Deprecated
        CRITICALITY_TYPE criticality = CRITICALITY_TYPE::LEVEL_A; /* required */
        bool systemPartition = false;                             /* required */
        name_t entryPoint;                                        /* required */

    public:
        Partition(identifier_t id, PROCESSOR_CORE_ID_TYPE afinity, name_t name,
                  decOrHex_t duration, decOrHex_t period,
                  std::vector<MemoryRegion> mem,
                  std::vector<QueuingPort> queuing,
                  std::vector<SamplingPort> sampling):
                  partitionIdentifier(id), affinity(affinity), partitionName(name), memoryRegions(mem),
                  duration(duration), period(period), samplePorts(sampling), queuePorts(queuing) {}
};

#endif
