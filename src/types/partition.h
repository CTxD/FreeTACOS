#ifndef PARTITION_H
#define PARTITION_H

#include "process.h"
#include "port_type.h"
#include "memory_requirements.h"

class Partition
{
    private:
        identifier_t partitionIdentifier;       /* required */
        affinity_t affinity = affinity_t::ANY;  /* required */
        name_t partitionName;                   /* required */

        decOrHex_t duration;                    /* required */
        decOrHex_t period;                      /* required */

        std::vector<MemoryRegion> memoryRegions;/* required */
        std::vector<QueuingPort> queuePorts;    /* required */
        std::vector<SamplingPort> samplePorts;  /* required */

        // Deprecated
        criticality_t criticality;                  /* required */
        bool systemPartition;                       /* required */
        name_t entryPoint;                          /* required */
        std::vector<SamplingPort> samplingPort;     /* required */
        std::vector<QueuingPort> queuingPort;       /* required */
        std::vector<Process> process;               /* required */

    public:
        Partition(identifier_t id, name_t name, affinity_t afinity,
                  decOrHex_t duration, decOrHex_t period,
                  std::vector<MemoryRegion> mem,
                  std::vector<QueuingPort> queuing,
                  std::vector<SamplingPort> sampling):
                  partitionIdentifier(id), affinity(affinity), partitionName(name), memoryRegions(mem),
                  duration(duration), period(period), samplePorts(sampling), queuePorts(queuing) {}
};

#endif
