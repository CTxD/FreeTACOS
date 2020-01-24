#include <arch.h>
#include "processchedule.hpp"
#include <process.hpp>
#include <partition.hpp>
#include "arinc_module.cpp"
#include "arinc_module.hpp"
#include <vector>

std::vector<Process> getProcessSchedule(long unsigned int partitionIdentifier)
{   
    //std::vector<Process> processOne;
    //processOne.push_back({4, 3, 1, {3,2,nullptr, 1024, 3,4,"One" }});
    //vector<Process> processList((),)
    /* std::vector<Partition> partitionList = arincModule.getPartitions();
    for(Partition partition : partitionList)
    {
        if(partition.getPartitionIdentifier() == partitionIdentifier)
        {
            return partition.getProcesses();
        }
        else
        {
            continue;
        }
        
    }
    
    std::vector<Process> processList = partitionList[0].getProcesses();
    auto asd = processList[2].getProcessIdentifier();
    CLogger::Get()->Write("processSchedule", LogNotice, "process identifier = %d", *(&asd)); */
}

void getNextProcess()
{

}

void ProcessSchedule()
{
    
    CLogger::Get()->Write("processSchedule", LogNotice, "status");
    CLogger::Get()->Write("processSchedule", LogNotice, "module = %d", arincModule.getModuleId());
    //std::vector<Partition> partitionList = arincModule.getPartitions();
    //std::vector<Process> processList = partitionList[0].getProcesses();
    //auto asd = processList[2].getProcessIdentifier();
    //CLogger::Get()->Write("processSchedule", LogNotice, "process identifier = %d", *(&asd));
    //std::vector<Process> processList = getProcessSchedule(2);
    // std::vector<Process> processReadyList = setProcessStusus(processList);
    
} 