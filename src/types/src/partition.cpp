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
    criticality = rhs.criticxality;
    systemPartition = rhs.systemPartition;
    entryPoint = rhs.entryPoint;
    return *this;
}

const PROCESSOR_CORE_ID_TYPE& Partition::getAffinity() const
{
    return affinity;
}

const name_t& Partition::getPartitionName() const
{
    return partitionName;
}

const vector<MemoryRegion>& Partition::getMemoryRegions() const
{
    return memoryRegions;
}

const vector<QueuingPort>& Partition::getQueuePorts() const
{
    return queuePorts;
}

const vector<SamplingPort>& Partition::getSamplePorts() const
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

const vector<Process>& Partition::getProcesses() const
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

RETURN_CODE_TYPE createProcess(PROCESS_ATTRIBUTE_TYPE attributes)
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
        if (strcmp(proc->attributes.NAME, attributes.NAME) == 0) {
            return RETURN_CODE_TYPE::NO_ACTION;
        }
    }
    if (attributes.STACK_SIZE < 0) {
        return RETURN_CODE_TYPE::INVALID_PARAM;
    }
    if (attributes.BASE_PRIORITY > MAX_PRIORITY_VALUE ||
        attributes.BASE_PRIORITY < MIN_PRIORITY_VALUE) {
        return RETURN_CODE_TYPE::INVALID_PARAM;
    }
    if (attributes.PERIOD < 0) {
        return RETURN_CODE_TYPE::INVALID_CONFIG;
    }
    if (attributes.TIME_CAPACITY < 0) {
        return RETURN_CODE_TYPE::INVALID_PARAM;
    }
    // process must be created during partition initialization
    if (mode == OPERATING_MODE_TYPE::NORMAL || mode == OPERATING_MODE_TYPE::IDLE) {
        return RETURN_CODE_TYPE::INVALID_MODE;
    }

    processes.push_back(Process(
        processes.size() + 1,
        {m_Timer.GetTicks() + attributes.TIME_CAPAC ITY, attributes.BASE_PRIORITY,
         PROCESS_STATE::DORMANT, attributes, DEFAULT_PROCESS_CORE_AFFINITY}));

    return RETURN_CODE_TYPE::NO_ERROR;
}

RETURN_CODE_TYPE Partition::checkPointer(void* ptr, APEX_INTEGER size)
{
    // check storage (insufficient storage capacity)
    // pok_check_ptr_or_return

    return RETURN_CODE_TYPE::NO_ERROR;
}
