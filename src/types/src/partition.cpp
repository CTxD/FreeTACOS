#include "partition.hpp"

Partition& Partition::operator=(const Partition& rhs)
{
    partitionName = rhs.partitionName;
    memoryRegions = rhs.memoryRegions;
    queuingPorts = rhs.queuingPorts;
    samplingPorts = rhs.samplingPorts;
    status = rhs.status;
    processes = rhs.processes;
    criticality = rhs.criticality;
    systemPartition = rhs.systemPartition;
    entryPoint = rhs.entryPoint;
    return *this;
}

const name_t& Partition::getPartitionName() const
{
    return partitionName;
}

const std::vector<MemoryRegion>& Partition::getMemoryRegions() const
{
    return *memoryRegions;
}

const std::vector<QueuingPort>& Partition::getQueuePorts() const
{
    return *queuingPorts;
}

const std::vector<SamplingPort>& Partition::getSamplePorts() const
{
    return *samplingPorts;
}

void Partition::setStatus(PARTITION_STATUS_TYPE status)
{
    status = std::move(status);
}

const PARTITION_STATUS_TYPE* Partition::getStatus() const
{
    return &(this->status);
}

void Partition::addProcess(Process proc)
{
    processes->push_back(proc);
}

const std::vector<Process>& Partition::getProcesses() const
{
    return *processes;
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

void Partition::setEntryPoint(name_t entry)
{
    entryPoint = std::move(entry);
}

const name_t& Partition::getEntryPoint() const
{
    return entryPoint;
}
