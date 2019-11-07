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
        MemoryRegion memoryRegion[100];
        monotonic_buffer_resource memoryRegionSrc{std::data(memoryRegion),
                                                    std::size(memoryRegion)};
        QueuingPort queuingPort[100];
        monotonic_buffer_resource queuingPortSrc{std::data(queuingPort),
                                                    std::size(queuingPort)};
        SamplingPort samplingPort[100];
        monotonic_buffer_resource samplingPortSrc{std::data(samplingPort),
                                                    std::size(samplingPort)};
        Process proces[100];
        monotonic_buffer_resource processSrc{std::data(proces),
                                                std::size(proces)};
        
        identifier_t partitionIdentifier;       /* required */
        PROCESSOR_CORE_ID_TYPE affinity = CORE_AFFINITY_NO_PREFERENCE;
        name_t partitionName;                   /* required */

        decOrHex_t duration;                    /* required */
        decOrHex_t period;                      /* required */

        vector<MemoryRegion> memoryRegions;     /* required */
        vector<QueuingPort> queuePorts;         /* required */
        vector<SamplingPort> samplePorts;       /* required */

        OPERATING_MODE_TYPE mode;
        PARTITION_STATUS_TYPE status;

        vector<Process> process;

    public:
        Partition() {};
        Partition(identifier_t id, PROCESSOR_CORE_ID_TYPE afinity, name_t name,
                  decOrHex_t duration, decOrHex_t period,
                  std::initializer_list<MemoryRegion> mem,
                  std::initializer_list<QueuingPort> queuing,
                  std::initializer_list<SamplingPort> sampling,
                  std::initializer_list<Process> proc):
                  partitionIdentifier(id), affinity(affinity), partitionName(name),
                  duration(duration), period(period), memoryRegions(mem, &memoryRegionSrc),
                  queuePorts(queuing, &queuingPortSrc), samplePorts(sampling, &samplingPortSrc),
                  process(proc, &processSrc) {}

};

#endif
