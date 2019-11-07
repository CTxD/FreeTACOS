#ifndef PARTITION_H
#define PARTITION_H

#include "process.h"
#include "apex_types.h"
#include "apex_error.h"
#include "queuing_port.h"
#include "sampling_port.h"
#include "apex_partition.h"
#include "memory_requirements.h"


class Partition
{
    private:
        identifier_t partitionIdentifier;   /* required */
        PROCESSOR_CORE_ID_TYPE affinity = CORE_AFFINITY_NO_PREFERENCE;
        name_t partitionName;               /* required */
        decOrHex_t duration;                /* required */
        decOrHex_t period;                  /* required */

        vector<MemoryRegion> memoryRegions;/* required */
        vector<QueuingPort> queuePorts;    /* required */
        vector<SamplingPort> samplePorts;  /* required */

        OPERATING_MODE_TYPE mode;
        PARTITION_STATUS_TYPE status;

        vector<Process> process;

        CRITICALITY_TYPE criticality = CRITICALITY_TYPE::LEVEL_A;
        bool systemPartition = false;
        name_t entryPoint;

    public:
        Partition(identifier_t id, PROCESSOR_CORE_ID_TYPE afinity, name_t name,
                  decOrHex_t duration, decOrHex_t period,
                  vector<MemoryRegion> mem,
                  vector<QueuingPort> queuing,
                  vector<SamplingPort> sampling):
                  partitionIdentifier(id), affinity(affinity), partitionName(name),
                  duration(duration), period(period), memoryRegions(mem),
                  queuePorts(queuing), samplePorts(sampling) {}

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
