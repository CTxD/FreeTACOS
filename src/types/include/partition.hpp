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

      Partition& operator=(const Partition&)
      {
        return *this;
      }

      Partition(const Partition&) {}

      identifier_t getPartitionIdentifier();

      PROCESSOR_CORE_ID_TYPE getAffinity();

      name_t getPartitionName();

      decOrHex_t getDuration();

      decOrHex_t getPeriod();

      vector<MemoryRegion> getMemoryRegions();

      vector<QueuingPort> getQueuePorts();

      vector<SamplingPort> getSamplePorts();

      void setMode(OPERATING_MODE_TYPE&& mode);

      OPERATING_MODE_TYPE getMode();

      void setStatus(PARTITION_STATUS_TYPE&& status);

      PARTITION_STATUS_TYPE getStatus();

      void addProcess(Process&& proc);

      vector<Process> getProcesses();

      void setCriticality(CRITICALITY_TYPE criticality);

      CRITICALITY_TYPE getCriticality();

      void setSystemPartition();

      bool getSystemPartition();

      void setEntryPoint();

      name_t getEntryPoint();
};

#endif
