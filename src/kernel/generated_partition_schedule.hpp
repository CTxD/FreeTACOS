#ifndef __GENERATED_PARTITION_SCHEDULE__
#define __GENERATED_PARTITION_SCHEDULE__
#include "core_schedule.hpp"

extern CoreSchedule coreSchedule = { // CoreSchedule
    {{                               // Core
      {
          // PartitionValues
          false,         // PeriodicProcessingStart
          6250000,       // Duration
          {"BlrSystem"}, // PartitionNameRef
          0,             // Offset
          7500000,       // Period
          2              // Affinity
      },

      {
          // PartitionValues
          false,              // PeriodicProcessingStart
          1250000,            // Duration
          {"DataProcessing"}, // PartitionNameRef
          10000000,           // Offset
          750000,             // Period
          2                   // Affinity
      },

      {
          // PartitionValues
          false,         // PeriodicProcessingStart
          6250000,       // Duration
          {"BlrSystem"}, // PartitionNameRef
          0,             // Offset
          7500000,       // Period
          2              // Affinity
      },

      {
          // PartitionValues
          false,              // PeriodicProcessingStart
          1250000,            // Duration
          {"DataProcessing"}, // PartitionNameRef
          10000000,           // Offset
          750000,             // Period
          2                   // Affinity
      },

      {
          // PartitionValues
          false,         // PeriodicProcessingStart
          6250000,       // Duration
          {"BlrSystem"}, // PartitionNameRef
          0,             // Offset
          7500000,       // Period
          2              // Affinity
      },

      {
          // PartitionValues
          false,              // PeriodicProcessingStart
          1250000,            // Duration
          {"DataProcessing"}, // PartitionNameRef
          10000000,           // Offset
          750000,             // Period
          2                   // Affinity
      }}}};
#endif