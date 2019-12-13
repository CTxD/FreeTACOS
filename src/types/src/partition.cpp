#include "include/partition.hpp"
#ifdef HOST_TESTING
#include <time.h>
#else
#include "arch.hpp"
#endif

Partition& Partition::operator=(const Partition& rhs)
{
    partitionIdentifier = rhs.partitionIdentifier;
    affinity = rhs.affinity;
    partitionName = rhs.partitionName;
    duration = rhs.duration;
    period = rhs.period;
    memoryRegions = rhs.memoryRegions;
    queuePorts = rhs.queuePorts;
    samplePorts = rhs.samplePorts;
    mode = rhs.mode;
    status = rhs.status;
    processes = rhs.processes;
    criticality = rhs.criticality;
    systemPartition = rhs.systemPartition;
    entryPoint = rhs.entryPoint;
    return *this;
}

const PROCESSOR_CORE_ID_TYPE& Partition::getAffinity() const
{
    return affinity;
}

const NAME_TYPE& Partition::getPartitionName() const
{
    return partitionName;
}

const std::vector<MemoryRegion, MonotonicAllocator<MemoryRegion>>& Partition::getMemoryRegions() const
{
    return memoryRegions;
}

const std::vector<QueuingPort, MonotonicAllocator<QueuingPort>>& Partition::getQueuePorts() const
{
    return queuePorts;
}

const std::vector<SamplingPort, MonotonicAllocator<SamplingPort>>& Partition::getSamplePorts() const
{
    return samplePorts;
}

void Partition::setMode(OPERATING_MODE_TYPE mode)
{
    mode = std::move(mode);
}

const OPERATING_MODE_TYPE& Partition::getMode() const
{
    return mode;
}

void Partition::setStatus(PARTITION_STATUS_TYPE status)
{
    status = std::move(status);
}

const PARTITION_STATUS_TYPE& Partition::getStatus() const
{
    return status;
}

const std::vector<Process, MonotonicAllocator<Process>>& Partition::getProcesses() const
{
    return processes;
}

void Partition::setCriticality(CRITICALITY_TYPE criticality)
{
    criticality = std::move(criticality);
}

const CRITICALITY_TYPE& Partition::getCriticality() const
{
    return criticality;
}

void Partition::setSystemPartition(bool systemPart)
{
    systemPartition = std::move(systemPart);
}

RETURN_CODE_TYPE Partition::checkPointer(SYSTEM_ADDRESS_TYPE ptr, STACK_SIZE_TYPE size)
{
    // check storage (insufficient storage capacity)
    // pok_check_ptr_in_partition
    for (auto& region : memoryRegions) {
        if (region.getAccessRights() == memory_access_t::READ_WRITE &&
            region.getType() == memory_region_t::RAM) {
            return region.createContext(ptr, size);
        }
    }

    return RETURN_CODE_TYPE::NO_ERROR;
}

const bool& Partition::getSystemPartition() const
{
    return systemPartition;
}

void Partition::setEntryPoint(SYSTEM_ADDRESS_TYPE entry)
{
    entryPoint = std::move(entry);
}

const SYSTEM_ADDRESS_TYPE& Partition::getEntryPoint() const
{
    return entryPoint;
}

void Partition::createProcess(PROCESS_ATTRIBUTE_TYPE attributes,
                              identifier_t& processId,
                              RETURN_CODE_TYPE& returnCode)
{
    processId = NULL;
    // check if partition storage capacity is sufficient
    returnCode = checkPointer(attributes.ENTRY_POINT, attributes.STACK_SIZE);

    if (processes.size() >= MAX_PROCESS_NUM) {
        returnCode = RETURN_CODE_TYPE::INVALID_CONFIG;
    }
    // process must have a unique name
    for (const auto& proc : processes) {
        // if (strcmp(proc.getAttributes().NAME.name, attributes.NAME.name) == 0) {
        //     return RETURN_CODE_TYPE::NO_ACTION;
        // }
    }
    if (attributes.STACK_SIZE <= 0) {
        returnCode = RETURN_CODE_TYPE::INVALID_PARAM;
    }
    if (attributes.BASE_PRIORITY > MAX_PRIORITY_VALUE ||
        attributes.BASE_PRIORITY < MIN_PRIORITY_VALUE) {
        returnCode = RETURN_CODE_TYPE::INVALID_PARAM;
    }
    if ((attributes.PERIOD % period) != 0 || attributes.PERIOD <= 0) {
        returnCode = RETURN_CODE_TYPE::INVALID_CONFIG;
    }
    if (attributes.TIME_CAPACITY <= 0) {
        returnCode = RETURN_CODE_TYPE::INVALID_PARAM;
    }
    // process must be created during partition initialization
    if (mode == OPERATING_MODE_TYPE::NORMAL) {
        returnCode = RETURN_CODE_TYPE::INVALID_MODE;
    }

    int t;
#ifdef HOST_TESTING
    t = clock();
#else
    t = CKernel::GetTimer().GetTicks();
#endif

    processId = processes.size() + 1;
    Process proc{processId,
                 {t + attributes.DEADLINE, attributes.BASE_PRIORITY,
                  PROCESS_STATE_TYPE::DORMANT, attributes, DEFAULT_PROCESS_CORE_AFFINITY}};
    processes.push_back(proc);

    returnCode = RETURN_CODE_TYPE::NO_ERROR;
}

void Partition::getProcess(identifier_t processId, Process& process, RETURN_CODE_TYPE& returnCode)
{
    for (const auto& proc : processes) {
        if (proc.getId() == processId)
            returnCode = RETURN_CODE_TYPE::NO_ERROR;
        process = proc;
    }
    returnCode = RETURN_CODE_TYPE::INVALID_PARAM;
    processId = NULL;
}
