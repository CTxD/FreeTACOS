#ifndef __GENERATED_PARTITION_SCHEDULE__
#define __GENERATED_PARTITION_SCHEDULE__
#include "core_schedule.hpp"

extern CoreSchedule coreSchedule = { // CoreSchedule
    {{                               // Core

      {
          // PartitionValues
          false,         // PeriodicProcessingStart
          5000000,       // Duration
          {"BlrSystem"}, // PartitionNameRef
          0,             // Offset
          10000000,      // Period
          2              // Affinity
      },

      {
          // PartitionValues
          false,              // PeriodicProcessingStart
          5000000,            // Duration
          {"DataProcessing"}, // PartitionNameRef
          10000000,           // Offset
          10000000,           // Period
          2                   // Affinity
      },

      {
          // PartitionValues
          false,         // PeriodicProcessingStart
          5000000,       // Duration
          {"BlrSystem"}, // PartitionNameRef
          0,             // Offset
          10000000,      // Period
          2              // Affinity
      },

      {
          // PartitionValues
          false,              // PeriodicProcessingStart
          5000000,            // Duration
          {"DataProcessing"}, // PartitionNameRef
          10000000,           // Offset
          10000000,           // Period
          2                   // Affinity
      },

      {
          // PartitionValues
          false,         // PeriodicProcessingStart
          5000000,       // Duration
          {"BlrSystem"}, // PartitionNameRef
          0,             // Offset
          10000000,      // Period
          2              // Affinity
      },

      {
          // PartitionValues
          false,              // PeriodicProcessingStart
          5000000,            // Duration
          {"DataProcessing"}, // PartitionNameRef
          10000000,           // Offset
          10000000,           // Period
          2                   // Affinity
      }}}};
#endif