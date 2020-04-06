#ifndef __GENERATED_PARTITION_SCHEDULE__
#define __GENERATED_PARTITION_SCHEDULE__
#include "core_schedule.hpp"

extern CoreSchedule coreSchedule = 
{ // CoreSchedule 
  {
    { // Core
            
        { // PartitionValues 
          false, // PeriodicProcessingStart 
          20000000, // Duration 
          {"IOProcessing"}, // PartitionNameRef 
          20000000, // Offset 
          100000000, // Period 
          0 // Affinity 
        }            ,    
          
        { // PartitionValues 
          false, // PeriodicProcessingStart 
          20000000, // Duration 
          {"systemManagement"}, // PartitionNameRef 
          0, // Offset 
          20000000, // Period 
          2 // Affinity 
        }      ,
        
        { // PartitionValues 
          false, // PeriodicProcessingStart 
          30000000, // Duration 
          {"flightManagement"}, // PartitionNameRef 
          40000000, // Offset 
          100000000, // Period 
          0 // Affinity 
        }            ,    
          
        { // PartitionValues 
          false, // PeriodicProcessingStart 
          20000000, // Duration 
          {"systemManagement"}, // PartitionNameRef 
          0, // Offset 
          20000000, // Period 
          2 // Affinity 
        }      ,
        
        { // PartitionValues 
          false, // PeriodicProcessingStart 
          10000000, // Duration 
          {"flightControls"}, // PartitionNameRef 
          30000000, // Offset 
          20000000, // Period 
          1 // Affinity 
        }            ,    
          
        { // PartitionValues 
          false, // PeriodicProcessingStart 
          20000000, // Duration 
          {"systemManagement"}, // PartitionNameRef 
          0, // Offset 
          20000000, // Period 
          2 // Affinity 
        }      ,
      
        { // PartitionValues 
          false, // PeriodicProcessingStart 
          10000000, // Duration 
          {"flightControls"}, // PartitionNameRef 
          30000000, // Offset 
          20000000, // Period 
          1 // Affinity 
        }      ,
        
        { // PartitionValues 
          false, // PeriodicProcessingStart 
          20000000, // Duration 
          {"IHVM "}, // PartitionNameRef 
          70000000, // Offset 
          200000000, // Period 
          0 // Affinity 
        }          }
  }
}; 
#endif