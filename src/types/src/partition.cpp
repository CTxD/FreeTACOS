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

const identifier_t& Partition::getPartitionIdentifier() const
{
  return partitionIdentifier;
}

const PROCESSOR_CORE_ID_TYPE& Partition::getAffinity() const
{
  return affinity;
}

const name_t& Partition::getPartitionName() const
{
  return partitionName;
}

const decOrHex_t& Partition::getDuration() const
{
  return duration;
}

const decOrHex_t& Partition::getPeriod() const
{
  return period;
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

void Partition::addProcess(Process proc)
{
  processes.push_back(proc);
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

void Partition::setEntryPoint(name_t entry)
{
  entryPoint = std::move(entry);
}

const name_t& Partition::getEntryPoint() const
{
  return entryPoint;
}
