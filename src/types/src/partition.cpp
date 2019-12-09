#include "include/partition.hpp"

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

RETURN_CODE_TYPE Partition::checkPointer(SYSTEM_ADDRESS_TYPE ptr, APEX_INTEGER size)
{
    // check storage (insufficient storage capacity)
    // pok_check_ptr_in_partition
    for (auto& region : memoryRegions) {
        if (region.getAccessRights() == memory_access_t::READ_WRITE &&
            region.getType() == memory_region_t::RAM) {
            if (region.createContext(ptr, size) == RETURN_CODE_TYPE::NO_ERROR) {
                //
            }
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

RETURN_CODE_TYPE Partition::createProcess(PROCESS_ATTRIBUTE_TYPE attributes)
{
    // check if partition storage capacity is sufficient
    if (checkPointer(attributes.ENTRY_POINT, attributes.STACK_SIZE) ==
        RETURN_CODE_TYPE::INVALID_CONFIG) {
        return RETURN_CODE_TYPE::INVALID_CONFIG;
    }
    if (processes.size() >= MAX_PROCESS_NUM) {
        return RETURN_CODE_TYPE::INVALID_CONFIG;
    }
    // process must have a unique name
    for (const auto& proc : processes) {
        // if (strcmp(proc.getAttributes().NAME.name, attributes.NAME.name) == 0) {
        //     return RETURN_CODE_TYPE::NO_ACTION;
        // }
    }
    if (attributes.STACK_SIZE <= 0) {
        return RETURN_CODE_TYPE::INVALID_PARAM;
    }
    if (attributes.BASE_PRIORITY > MAX_PRIORITY_VALUE ||
        attributes.BASE_PRIORITY < MIN_PRIORITY_VALUE) {
        return RETURN_CODE_TYPE::INVALID_PARAM;
    }
    if (attributes.PERIOD <= 0) {
        return RETURN_CODE_TYPE::INVALID_CONFIG;
    }
    if (attributes.TIME_CAPACITY <= 0) {
        return RETURN_CODE_TYPE::INVALID_PARAM;
    }
    // process must be created during partition initialization
    if (mode == OPERATING_MODE_TYPE::NORMAL || mode == OPERATING_MODE_TYPE::IDLE) {
        return RETURN_CODE_TYPE::INVALID_MODE;
    }

    // processes.push_back(Process(
    //     processes.size() + 1,
    //     {m_Timer.GetTicks() + attributes.TIME_CAPACITY, attributes.BASE_PRIORITY,
    //      PROCESS_STATE_TYPE::DORMANT, attributes, DEFAULT_PROCESS_CORE_AFFINITY}));

    return RETURN_CODE_TYPE::NO_ERROR;
}
