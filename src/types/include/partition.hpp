#ifndef PARTITION_H
#define PARTITION_H

#include <circle/memory.h>

#include "apex_error.h"
#include "apex_partition.h"
#include "apex_types.h"

#include "memory_requirements.hpp"
#include "process.hpp"
#include "queuing_port.hpp"
#include "sampling_port.hpp"

class Partition {
private:
    MemoryRegion memoryRegion[100];
    MemoryArea memoryRegionArea{std::data(memoryRegion), std::size(memoryRegion)};
    MonotonicMemoryResource<> memoryRegionSrc{memoryRegionArea};
    MonotonicAllocator<void> memoryRegionAllocator{memoryRegionSrc};

    QueuingPort queuingPort[100];
    MemoryArea queuePortArea{std::data(queuingPort), std::size(queuingPort)};
    MonotonicMemoryResource<> queuingPortSrc{queuePortArea};
    MonotonicAllocator<void> queuePortAllocator{queuingPortSrc};

    SamplingPort samplingPort[100];
    MemoryArea samplingPortArea{std::data(samplingPort), std::size(samplingPort)};
    MonotonicMemoryResource<> samplingPortSrc{samplingPortArea};
    MonotonicAllocator<void> samplingPortAllocator{samplingPortSrc};

    Process proces[100];
    MemoryArea processArea{std::data(proces), std::size(proces)};
    MonotonicMemoryResource<> processSrc{processArea};
    MonotonicAllocator<void> processAllocator{processSrc};

    identifier_t partitionIdentifier; /* required */
    PROCESSOR_CORE_ID_TYPE affinity = CORE_AFFINITY_NO_PREFERENCE;
    NAME_TYPE partitionName; /* required */

    decOrHex_t duration; /* required */
    decOrHex_t period;   /* required */

    std::vector<MemoryRegion, MonotonicAllocator<MemoryRegion>> memoryRegions{
        memoryRegionAllocator}; /* required */
    std::vector<QueuingPort, MonotonicAllocator<QueuingPort>> queuePorts{queuePortAllocator}; /* required */
    std::vector<SamplingPort, MonotonicAllocator<SamplingPort>> samplePorts{
        samplingPortAllocator}; /* required */

    OPERATING_MODE_TYPE mode;
    PARTITION_STATUS_TYPE status;

    std::vector<Process, MonotonicAllocator<Process>> processes{processAllocator};
    CRITICALITY_TYPE criticality = CRITICALITY_TYPE::LEVEL_A; /* required */
    bool systemPartition = false;                             /* required */
    NAME_TYPE entryPoint;                                        /* required */

public:
    Partition(){};

    Partition(identifier_t id,
              PROCESSOR_CORE_ID_TYPE affinity,
              NAME_TYPE name,
              decOrHex_t duration,
              decOrHex_t period,
              std::initializer_list<MemoryRegion> mem,
              std::initializer_list<QueuingPort> queuing,
              std::initializer_list<SamplingPort> sampling)
        : partitionIdentifier(id),
          affinity(affinity),
          partitionName(name),
          duration(duration),
          period(period),
          memoryRegions(mem),
          queuePorts(queuing),
          samplePorts(sampling)
    {
        // CMemorySystem::Get()->nBaseAddress;
    }

    Partition(identifier_t id,
              PROCESSOR_CORE_ID_TYPE affinity,
              NAME_TYPE name,
              decOrHex_t duration,
              decOrHex_t period,
              std::initializer_list<MemoryRegion> mem,
              std::initializer_list<QueuingPort> queuing,
              std::initializer_list<SamplingPort> sampling,
              std::initializer_list<Process> proc)
        : partitionIdentifier(id),
          affinity(affinity),
          partitionName(name),
          duration(duration),
          period(period),
          memoryRegions(mem),
          queuePorts(queuing),
          samplePorts(sampling)
    {
    }

    Partition(const Partition& rhs)
        : partitionIdentifier(rhs.partitionIdentifier),
          affinity(rhs.affinity),
          partitionName(rhs.partitionName),
          duration(rhs.duration),
          period(rhs.period),
          memoryRegions(rhs.memoryRegions),
          queuePorts(rhs.queuePorts),
          samplePorts(rhs.samplePorts),
          processes(rhs.processes)
    {
    }

    Partition& operator=(const Partition& rhs);

    const identifier_t& getPartitionIdentifier() const;

    const PROCESSOR_CORE_ID_TYPE& getAffinity() const;

    const NAME_TYPE& getPartitionName() const;

    const decOrHex_t& getDuration() const;

    const decOrHex_t& getPeriod() const;

    const std::vector<MemoryRegion>& getMemoryRegions() const;

    const std::vector<QueuingPort>& getQueuePorts() const;

    const std::vector<SamplingPort>& getSamplePorts() const;

    void setMode(OPERATING_MODE_TYPE mode);

    const OPERATING_MODE_TYPE& getMode() const;

    void setStatus(PARTITION_STATUS_TYPE status);

    const PARTITION_STATUS_TYPE& getStatus() const;

    void addProcess(Process proc);

    const std::vector<Process>& getProcesses() const;

    void setCriticality(CRITICALITY_TYPE criticality);

    const CRITICALITY_TYPE& getCriticality() const;

    void setSystemPartition(bool systemPart);

    const bool& getSystemPartition() const;

    void setEntryPoint(NAME_TYPE entry);

    const NAME_TYPE& getEntryPoint() const;
};

#endif
