#ifndef PARTITION_H
#define PARTITION_H

#include "apex_error.h"
#include "apex_partition.hpp"
#include "apex_types.h"

#include "memory_requirements.hpp"
#include "process.hpp"
#include "queuing_port.hpp"
#include "sampling_port.hpp"
#include <circle/sched/task.h>
#include <vector>

class Partition {
private:
    name_t partitionName;             /* required */
    APEX_INTEGER partitionIdentifier; /* required */
    APEX_UNSIGNED affinity = CORE_AFFINITY_NO_PREFERENCE;

    decOrHex_t duration; /* required */
    decOrHex_t period;   /* required */

    OPERATING_MODE_TYPE mode;
    OPERATING_MODE_TYPE partitionOperationMode;
    START_CONDITION_TYPE partitionstartCondition;
    PARTITION_STATUS_TYPE status;

    CRITICALITY_TYPE criticality = CRITICALITY_TYPE::LEVEL_A; /* required */
    bool systemPartition = false;                             /* required */
    name_t entryPoint;                                        /* required */

    MemoryRegion memoryRegion[10];
    std::vector<MemoryRegion>* memoryRegions = new (&memoryRegion) std::vector<MemoryRegion>;

    QueuingPort queuingPort[10];
    std::vector<QueuingPort>* queuingPorts = new (&queuingPort) std::vector<QueuingPort>;

    SamplingPort samplingPort[10];
    std::vector<SamplingPort>* samplingPorts = new (&samplingPort) std::vector<SamplingPort>;

    std::optional<Process> process[10];
    std::vector<Process>* processes = new (&process) std::vector<Process>;

public:
    Partition(){};

    Partition(name_t name,
              decOrHex_t id,
              APEX_UNSIGNED affinity,
              decOrHex_t duration,
              decOrHex_t period,
              std::initializer_list<MemoryRegion> mem,
              std::initializer_list<QueuingPort> queuing,
              std::initializer_list<SamplingPort> sampling,
              std::initializer_list<Process> proc)
    {
        this->partitionName = name;
        status = {id, affinity, duration, period};

        for (auto m : mem) {
            memoryRegions->push_back(m);
        }
        for (auto q : queuing) {
            queuingPorts->push_back(q);
        }
        for (auto p : proc) {
            processes->push_back(p);
        }
    }

    Partition& operator=(const Partition& rhs);

    const name_t& getPartitionName() const;

    const std::vector<MemoryRegion>& getMemoryRegions() const;

    const std::vector<QueuingPort>& getQueuePorts() const;

    const std::vector<SamplingPort>& getSamplePorts() const;

    void setStatus(PARTITION_STATUS_TYPE status);

    const PARTITION_STATUS_TYPE* getStatus() const;

    void addProcess(Process proc);

    const std::vector<Process>& getProcesses() const;

    void setCriticality(CRITICALITY_TYPE criticality);

    const CRITICALITY_TYPE& getCriticality() const;

    void setSystemPartition(bool systemPart);

    const bool& getSystemPartition() const;

    void setEntryPoint(name_t entry);

    const name_t& getEntryPoint() const;
};

#endif
