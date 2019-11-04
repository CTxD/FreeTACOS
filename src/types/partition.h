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
                  partitionIdentifier(id), affinity(affinity), partitionName(name),
                  duration(duration), period(period), memoryRegions(mem),
                  queuePorts(queuing), samplePorts(sampling) {}

          // Partition(const Partition& p): partitionIdentifier(p.partitionIdentifier),
          //   affinity(p.affinity), partitionName(p.partitionName), duration(p.duration),
          //   period(p.period), memoryRegions(p.memoryRegions), queuePorts(p.queuePorts),
          //   samplePorts(p.samplePorts) {}
          //
          // Partition& operator=(Partition&& rhs)
          // {
          //     partitionIdentifier = std::move(rhs.partitionIdentifier);
          //     affinity = std::move(rhs.affinity);
          //     partitionName = std::move(rhs.partitionName);
          //     duration = std::move(rhs.duration);
          //     period = std::move(rhs.period);
          //     memoryRegions = std::move(rhs.memoryRegions);
          //     // queuePorts = std::move(rhs.queuePorts);
          //     // samplePorts = std::move(rhs.samplePorts);
          //     return *this;
          // }
};

#endif
