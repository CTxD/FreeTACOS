#ifndef PARTITION_H
#define PARTITION_H

#include "apex_types.h"
#include "apex_error.h"
#include "apex_partition.h"

#include "process.hpp"
#include "queuing_port.hpp"
#include "sampling_port.hpp"
#include "memory_requirements.hpp"


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

      vector<Process> processes;
      CRITICALITY_TYPE criticality = CRITICALITY_TYPE::LEVEL_A; /* required */
      bool systemPartition = false;                             /* required */
      name_t entryPoint;                                        /* required */

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
        processes(proc, &processSrc) {}

      Partition(const Partition& rhs):
        partitionIdentifier(rhs.partitionIdentifier), affinity(rhs.affinity),
        partitionName(rhs.partitionName), duration(rhs.duration), period(rhs.period),
        memoryRegions(rhs.memoryRegions), queuePorts(rhs.queuePorts), samplePorts(rhs.samplePorts),
        processes(rhs.processes) {}

      Partition& operator=(const Partition& rhs);

      const identifier_t& getPartitionIdentifier() const;

      const PROCESSOR_CORE_ID_TYPE& getAffinity() const;

      const name_t& getPartitionName() const;

      const decOrHex_t& getDuration() const;

      const decOrHex_t& getPeriod() const;

      const vector<MemoryRegion>& getMemoryRegions() const;

      const vector<QueuingPort>& getQueuePorts() const;

      const vector<SamplingPort>& getSamplePorts() const;

      void setMode(OPERATING_MODE_TYPE mode);

      const OPERATING_MODE_TYPE& getMode() const;

      void setStatus(PARTITION_STATUS_TYPE status);

      const PARTITION_STATUS_TYPE& getStatus() const;

      void addProcess(Process proc);

      const vector<Process>& getProcesses() const;

      void setCriticality(CRITICALITY_TYPE criticality);

      const CRITICALITY_TYPE& getCriticality() const;

      void setSystemPartition(bool systemPart);

      const bool& getSystemPartition() const;

      void setEntryPoint(name_t entry);

      const name_t& getEntryPoint() const;
};

#endif
