#ifndef PARTITION_H
#define PARTITION_H

#include "apex_error.h"
#include "apex_partition.h"
#include "apex_types.h"

#include "memory_requirements.hpp"
#include "process.hpp"
#include "queuing_port.hpp"
#include "sampling_port.hpp"

const int MAX_PROCESS_NUM = 100;

class Partition {
private:
    MemoryRegion memoryRegion[100];
    MemoryArea memoryRegionArea{std::data(memoryRegion), std::size(memoryRegion)};
    MonotonicMemoryResource<> memoryRegionSrc{memoryRegionArea};
    MonotonicAllocator<MemoryRegion> memoryRegionAllocator{memoryRegionSrc};

    QueuingPort queuingPort[100];
    MemoryArea queuePortArea{std::data(queuingPort), std::size(queuingPort)};
    MonotonicMemoryResource<> queuingPortSrc{queuePortArea};
    MonotonicAllocator<QueuingPort> queuePortAllocator{queuingPortSrc};

    SamplingPort samplingPort[100];
    MemoryArea samplingPortArea{std::data(samplingPort), std::size(samplingPort)};
    MonotonicMemoryResource<> samplingPortSrc{samplingPortArea};
    MonotonicAllocator<SamplingPort> samplingPortAllocator{samplingPortSrc};

    Process proc[MAX_PROCESS_NUM];
    MemoryArea processArea{std::data(proc), std::size(proc)};
    MonotonicMemoryResource<> processSrc{processArea};
    MonotonicAllocator<Process> processAllocator{processSrc};

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

    OPERATING_MODE_TYPE mode = OPERATING_MODE_TYPE::IDLE;
    PARTITION_STATUS_TYPE status;

    std::vector<Process, MonotonicAllocator<Process>> processes{processAllocator};
    CRITICALITY_TYPE criticality = CRITICALITY_TYPE::LEVEL_A; /* required */
    bool systemPartition = false;                             /* required */
    SYSTEM_ADDRESS_TYPE entryPoint;                           /* required */

public:
    Partition(){};

    Partition(identifier_t id,
              PROCESSOR_CORE_ID_TYPE affinity,
              std::string name,
              decOrHex_t duration,
              decOrHex_t period,
              std::vector<MemoryRegion> mem,
              std::vector<QueuingPort> queuing,
              std::vector<SamplingPort> sampling)
        : partitionIdentifier(id), affinity(affinity), partitionName(name), duration(duration),
          period(period)
    {
      for(auto reg: mem){
        memoryRegions.push_back(reg);
      }
      for(auto queue: queuing){
        queuePorts.push_back(queue);
      }
      for(auto sample: sampling){
        samplePorts.push_back(sample);
      }

      mode = OPERATING_MODE_TYPE::COLD_START;
      // CMemorySystem::Get()->nBaseAddress;
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

    const std::vector<MemoryRegion, MonotonicAllocator<MemoryRegion>>& getMemoryRegions() const;

    const std::vector<QueuingPort, MonotonicAllocator<QueuingPort>>& getQueuePorts() const;

    const std::vector<SamplingPort, MonotonicAllocator<SamplingPort>>& getSamplePorts() const;

    RETURN_CODE_TYPE checkPointer(SYSTEM_ADDRESS_TYPE ptr, STACK_SIZE_TYPE size);

    void setMode(OPERATING_MODE_TYPE m);

    const OPERATING_MODE_TYPE& getMode() const;

    void setStatus(PARTITION_STATUS_TYPE s);

    void getProcessStatus(identifier_t id, PROCESS_STATUS_TYPE& s, RETURN_CODE_TYPE& returnCode);

    const PARTITION_STATUS_TYPE& getStatus() const;

    void addProcess(Process proc);

    const std::vector<Process, MonotonicAllocator<Process>>& getProcesses() const;

    void getProcess(identifier_t processId, Process& proc, RETURN_CODE_TYPE& returnCode);

    void createProcess(PROCESS_ATTRIBUTE_TYPE attributes,
                       identifier_t& processId,
                       RETURN_CODE_TYPE& returnCode);

    void setCriticality(CRITICALITY_TYPE criticality);

    const CRITICALITY_TYPE& getCriticality() const;

    void setSystemPartition(bool systemPart);

    const bool& getSystemPartition() const;

    void setEntryPoint(SYSTEM_ADDRESS_TYPE entry);

    const SYSTEM_ADDRESS_TYPE& getEntryPoint() const;
};

#endif
