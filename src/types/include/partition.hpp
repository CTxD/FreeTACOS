#ifndef PARTITION_H
#define PARTITION_H

#include "apex_error.h"
#include "apex_partition.h"
#include "apex_types.h"

#include "memory_requirements.hpp"
#include "process.hpp"
#include "queuing_port.hpp"
#include "sampling_port.hpp"
#include <vector>

const int MAX_PROCESS_NUM = 100;

class Partition {
private:
    identifier_t partitionIdentifier; /* required */
    PROCESSOR_CORE_ID_TYPE affinity = CORE_AFFINITY_NO_PREFERENCE;
    NAME_TYPE partitionName; /* required */

    decOrHex_t duration; /* required */
    decOrHex_t period;   /* required */

    OPERATING_MODE_TYPE mode = OPERATING_MODE_TYPE::IDLE;
    PARTITION_STATUS_TYPE status;

    CRITICALITY_TYPE criticality = CRITICALITY_TYPE::LEVEL_A; /* required */
    bool systemPartition = false;                             /* required */
    SYSTEM_ADDRESS_TYPE entryPoint;                           /* required */

    MemoryRegion memoryRegion[1];
    std::vector<MemoryRegion>* memoryRegions = new (&memoryRegion) std::vector<MemoryRegion>;

    QueuingPort queuingPort[1];
    std::vector<QueuingPort>* queuingPorts = new (&queuingPort) std::vector<QueuingPort>;

    SamplingPort samplingPort[1];
    std::vector<SamplingPort>* samplingPorts = new (&samplingPort) std::vector<SamplingPort>;

    std::optional<Process> process[1];
    std::vector<Process>* processes = new (&process) std::vector<Process>;

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
        : partitionIdentifier(id),
          affinity(affinity),
          partitionName(name),
          duration(duration),
          period(period)
    {
        for (auto m : mem) {
            memoryRegions->push_back(m);
        }
        for (auto q : queuing) {
            queuingPorts->push_back(q);
        }
        for (auto s : sampling) {
            samplingPorts->push_back(s);
        }
        mode = OPERATING_MODE_TYPE::COLD_START;
    }

    Partition(identifier_t id,
              PROCESSOR_CORE_ID_TYPE affinity,
              name_t name,
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
          period(period)
    {
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

    Partition(const Partition& rhs)
        : partitionIdentifier(rhs.partitionIdentifier),
          affinity(rhs.affinity),
          partitionName(rhs.partitionName),
          duration(rhs.duration),
          period(rhs.period)
    {
        for (auto m : rhs.getMemoryRegions()) {
            memoryRegions->push_back(m);
        }
        for (auto q : rhs.getQueuePorts()) {
            queuingPorts->push_back(q);
        }
        for (auto s : rhs.getSamplePorts()) {
            samplingPorts->push_back(s);
        }
        for (auto p : rhs.getProcesses()) {
            processes->push_back(p);
        }
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

    RETURN_CODE_TYPE checkPointer(SYSTEM_ADDRESS_TYPE ptr, STACK_SIZE_TYPE size, TTaskRegisters& regs);

    void setMode(OPERATING_MODE_TYPE m);

    const OPERATING_MODE_TYPE& getMode() const;

    void setStatus(PARTITION_STATUS_TYPE s);

    void getProcessStatus(identifier_t id, PROCESS_STATUS_TYPE& s, RETURN_CODE_TYPE& returnCode);

    const PARTITION_STATUS_TYPE& getStatus() const;

    void addProcess(Process proc);

    const std::vector<Process>& getProcesses() const;

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
