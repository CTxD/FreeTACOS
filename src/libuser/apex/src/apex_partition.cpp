#include <apex_partition.hpp>
#include <partitionscheduling.hpp>
#include <arinc_module.hpp>

static void GET_PARTITION_STATUS(
    /*out*/ const PARTITION_STATUS_TYPE* PARTITION_STATUS,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE){

    auto* currentPartition = CyclicExecutiveSchedule::GetCurrentPartition();
    auto& module = ArincModule::generatedArincModule;

    for (auto& partition : module.partitions) {
        if(*partition.getPartitionName().x.x == *currentPartition->partitionName.x){
            *RETURN_CODE = RETURN_CODE_TYPE::NO_ERROR;
            PARTITION_STATUS = partition.getStatus();
        }
    }
}