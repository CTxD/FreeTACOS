#include "types/arinc_module.h"

int main() {

  PartitionHMTable partitionHMBuffer[125];
  monotonic_buffer_resource partitionHMMemory{std::data(partitionHMBuffer), std::size(partitionHMBuffer)};
  


  Partition part = { // Partition
    1, // Identifier
    0, // Affinity
    {"systemManagement"}, // Name
    20000000, // Duration
    100000000, // Period
    { // MemoryRegion
      { // Region
        {"mainMemory"}, // Name
        memory_region_t::RAM, // Type
        1048576, // Size
        memory_access_t::READ_WRITE, // AccessRights
        {}, // Address
      },
      { // Region
        {"Flash"}, // Name
        memory_region_t::FLASH, // Type
        524288, // Size
        memory_access_t::READ_ONLY, // AccessRights
        {}, // Address
      }
    },
    { // Queuing
      { //Queuing
        {"Stat_5Dq"}, // Name
        30 , // MaxMessageSize
        PORT_DIRECTION_TYPE::DESTINATION, // Direction
        30, // MaxNbMessage
      },
      { //Queuing
        {"Stat_4Dq"}, // Name
        30 , // MaxMessageSize
        PORT_DIRECTION_TYPE::DESTINATION, // Direction
        30, // MaxNbMessage
      },
      { //Queuing
        {"Stat_3Dq"}, // Name
        30 , // MaxMessageSize
        PORT_DIRECTION_TYPE::DESTINATION, // Direction
        30, // MaxNbMessage
      },
      { // Queuing
        {"Stat_2Dq"}, // Name
        30 , // MaxMessageSize
        PORT_DIRECTION_TYPE::DESTINATION, // Direction
        30, // MaxNbMessage
      }
    },
    {} // Sampling
  };

  int i = 5;

  ArincModule arincModule ={
      {"MyModule"}, // Name
      { }, // ModuleVersion
      { }, // moduleId
      { // Partitions
        { // Partition
          1, // Identifier
          0, // Affinity
          {"systemManagement"}, // Name
          20000000, // Duration
          100000000, // Period
          { // MemoryRegion
            { // Region
              {"mainMemory"}, // Name
              memory_region_t::RAM, // Type
              1048576, // Size
              memory_access_t::READ_WRITE, // AccessRights
              {}, // Address
            },
            { // Region
              {"Flash"}, // Name
              memory_region_t::FLASH, // Type
              524288, // Size
              memory_access_t::READ_ONLY, // AccessRights
              {}, // Address
            }
          },
          { // Queuing
            { //Queuing
              {"Stat_5Dq"}, // Name
              30 , // MaxMessageSize
              PORT_DIRECTION_TYPE::DESTINATION, // Direction
              30, // MaxNbMessage
            },
            { //Queuing
              {"Stat_4Dq"}, // Name
              30 , // MaxMessageSize
              PORT_DIRECTION_TYPE::DESTINATION, // Direction
              30, // MaxNbMessage
            },
            { //Queuing
              {"Stat_3Dq"}, // Name
              30 , // MaxMessageSize
              PORT_DIRECTION_TYPE::DESTINATION, // Direction
              30, // MaxNbMessage
            },
            { // Queuing
              {"Stat_2Dq"}, // Name
              30 , // MaxMessageSize
              PORT_DIRECTION_TYPE::DESTINATION, // Direction
              30, // MaxNbMessage
            }
          },
          {}
        },
        { // Partition
          2, // Identifier
          0, // Affinity
          {"flightControls"}, // Name
          10000000, // Duration
          100000000, // Period
          { // MemoryRegion
            { // Region
              {"mainMemory"}, // Name
              memory_region_t::RAM, // Type
              1048576, // Size
              memory_access_t::READ_WRITE, // AccessRights
              {}, // Address
            },
            { // Region
              {"Flash"}, // Name
              memory_region_t::FLASH, // Type
              524288, // Size
              memory_access_t::READ_ONLY, // AccessRights
              {}, // Address
            }
          },
          { // Queuing
            { // Queuing
              {"Stat_2Sq"}, // Name
              30 , // MaxMessageSize
              PORT_DIRECTION_TYPE::SOURCE, // Direction
              30, // MaxNbMessage
            }
          },
          { // Sampling
            { // Sampling
              {"Sens_2Ds"}, // Name
              40, // MaxMessageSize
              PORT_DIRECTION_TYPE::DESTINATION, // Direction
              {}, // RefreshRate
            },
            { // Sampling
              {"Sens_1Ds"}, // Name
              40, // MaxMessageSize
              PORT_DIRECTION_TYPE::DESTINATION, // Direction
              {}, // RefreshRate
            },
            { // Sampling
              {"Act_2Ss"}, // Name
              20, // MaxMessageSize
              PORT_DIRECTION_TYPE::SOURCE, // Direction
              {}, // RefreshRate
            },
            { // Sampling
              {"Act_1Ss"}, // Name
              20, // MaxMessageSize
              PORT_DIRECTION_TYPE::SOURCE, // Direction
              {}, // RefreshRate
            }
          }
        },
        { // Partition
          3, // Identifier
          0, // Affinity
          {"flightManagement"}, // Name
          30000000, // Duration
          100000000, // Period
          { // MemoryRegion
            { // Region
              {"mainMemory"}, // Name
              memory_region_t::RAM, // Type
              1048576, // Size
              memory_access_t::READ_WRITE, // AccessRights
              {}, // Address
            },
            { // Region
              {"Flash"}, // Name
              memory_region_t::FLASH, // Type
              524288, // Size
              memory_access_t::READ_ONLY, // AccessRights
              {}, // Address
            }
          },
          { // Queuing
            { // Queuing
              {"Stat_3Sq"}, // Name
              30 , // MaxMessageSize
              PORT_DIRECTION_TYPE::SOURCE, // Direction
              30, // MaxNbMessage
            }
          },
          { // Sampling
            { // Sampling
              {"Sens_2Ds"}, // Name
              40, // MaxMessageSize
              PORT_DIRECTION_TYPE::DESTINATION, // Direction
              {}, // RefreshRate
            }
          }
        },
        { // Partition
          4, // Identifier
          0, // Affinity
          {"IOProcessing"}, // Name
          20000000, // Duration
          100000000, // Period
          { // MemoryRegion
            { // Region
              {"mainMemory"}, // Name
              memory_region_t::RAM, // Type
              1048576, // Size
              memory_access_t::READ_WRITE, // AccessRights
              {}, // Address
            },
            { // Region
              {"Flash"}, // Name
              memory_region_t::FLASH, // Type
              524288, // Size
              memory_access_t::READ_ONLY, // AccessRights
              {}, // Address
            },
            { // Region
              {"IORegion"}, // Name
              memory_region_t::INPUT_OUTPUT, // Type
              524288, // Size
              memory_access_t::READ_WRITE, // AccessRights
              {}, // Address
            }
          },
          { // Queuing
            { // Queuing
              {"Stat_4Sq"}, // Name
              30 , // MaxMessageSize
              PORT_DIRECTION_TYPE::SOURCE, // Direction
              30, // MaxNbMessage
            }
          },
          {}
        },
        { // Partition
          5, // Identifier
          0, // Affinity
          {"IHVM "}, // Name
          20000000, // Duration
          200000000, // Period
          { // MemoryRegion
            { // Region
              {"mainMemory"}, // Name
              memory_region_t::RAM, // Type
              1048576, // Size
              memory_access_t::READ_WRITE, // AccessRights
              {}, // Address
            },
            { // Region
              {"Flash"}, // Name
              memory_region_t::FLASH, // Type
              524288, // Size
              memory_access_t::READ_ONLY, // AccessRights
              {}, // Address
            }
          },
          { // Queuing
            { // Queuing
              {"Stat_5Sq"}, // Name
              30 , // MaxMessageSize
              PORT_DIRECTION_TYPE::SOURCE, // Direction
              30, // MaxNbMessage
            }
          },
          { // Sampling
            { // Sampling
              {"Act_2Ds"}, // Name
              20, // MaxMessageSize
              PORT_DIRECTION_TYPE::DESTINATION, // Direction
              {}, // RefreshRate
            },
            { // Sampling
              {"Act_1Ds"}, // Name
              20, // MaxMessageSize
              PORT_DIRECTION_TYPE::DESTINATION, // Direction
              {}, // RefreshRate
            }
          }
        }
      }
//       // { // Schedules
//       //   { // PartitionTimeWindows
//       //     {
//       //       false, // PeriodicProcessingStart
//       //       20000000, // Duration
//       //       {"systemManagement"}, // PartitionNameRef
//       //       0, // Offset
//       //     },
//       //     {
//       //       false, // PeriodicProcessingStart
//       //       10000000, // Duration
//       //       {"IOProcessing"}, // PartitionNameRef
//       //       20000000, // Offset
//       //     },
//       //     {
//       //       false, // PeriodicProcessingStart
//       //       10000000, // Duration
//       //       {"flightControl"}, // PartitionNameRef
//       //       30000000, // Offset
//       //     },
//       //     {
//       //       false, // PeriodicProcessingStart
//       //       30000000, // Duration
//       //       {"flightManagement"}, // PartitionNameRef
//       //       40000000, // Offset
//       //     },
//       //     {
//       //       false, // PeriodicProcessingStart
//       //       10000000, // Duration
//       //       {"IOProcessing"}, // PartitionNameRef
//       //       70000000, // Offset
//       //     },
//       //     {
//       //       false, // PeriodicProcessingStart
//       //       20000000, // Duration
//       //       {"systemManagement"}, // PartitionNameRef
//       //       100000000, // Offset
//       //     },
//       //     {
//       //       false, // PeriodicProcessingStart
//       //       10000000, // Duration
//       //       {"IOProcessing"}, // PartitionNameRef
//       //       120000000, // Offset
//       //     },
//       //     {
//       //       false, // PeriodicProcessingStart
//       //       10000000, // Duration
//       //       {"flightControl"}, // PartitionNameRef
//       //       130000000, // Offset
//       //     },
//       //     {
//       //       false, // PeriodicProcessingStart
//       //       30000000, // Duration
//       //       {"flightManagement"}, // PartitionNameRef
//       //       140000000, // Offset
//       //     },
//       //     {
//       //       false, // PeriodicProcessingStart
//       //       10000000, // Duration
//       //       {"IOProcessing"}, // PartitionNameRef
//       //       170000000, // Offset
//       //     },
//       //     {
//       //       false, // PeriodicProcessingStart
//       //       20000000, // Duration
//       //       {"IVHM "}, // PartitionNameRef
//       //       180000000, // Offset
//       //     }
//       //   }
//       // },
//       // { // SystemError
//       //   {
//       //     1, // ErrorIdentifier
//       //     {"Configuration Error"}, // Description
//       //   },
//       //   {
//       //     2, // ErrorIdentifier
//       //     {"Module Config Error"}, // Description
//       //   },
//       //   {
//       //     3, // ErrorIdentifier
//       //     {"partition config error"}, // Description
//       //   },
//       //   {
//       //     4, // ErrorIdentifier
//       //     {"partition init error"}, // Description
//       //   },
//       //   {
//       //     5, // ErrorIdentifier
//       //     {"segmentation error"}, // Description
//       //   },
//       //   {
//       //     6, // ErrorIdentifier
//       //     {"time duration exceeded"}, // Description
//       //   },
//       //   {
//       //     7, // ErrorIdentifier
//       //     {"invalid OS call"}, // Description
//       //   },
//       //   {
//       //     8, // ErrorIdentifier
//       //     {"divide by 0"}, // Description
//       //   },
//       //   {
//       //     9, // ErrorIdentifier
//       //     {"floating point error"}, // Description
//       //   }
//       // },
//       // { // MultiPartitionHM
//       //   {
//       //     {"Avionic partitions HM table"}, // TableName
//       //     { // SystemError
//       //       { // ErrorAction
//       //         3, // ErrorIdentifierRef
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorAction
//       //       },
//       //       { // ErrorAction
//       //         4, // ErrorIdentifierRef
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorAction
//       //       },
//       //       { // ErrorAction
//       //         5, // ErrorIdentifierRef
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorAction
//       //       },
//       //       { // ErrorAction
//       //         6, // ErrorIdentifierRef
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorAction
//       //       },
//       //       { // ErrorAction
//       //         7, // ErrorIdentifierRef
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorAction
//       //       },
//       //       { // ErrorAction
//       //         8, // ErrorIdentifierRef
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorAction
//       //       },
//       //       { // ErrorAction
//       //         9, // ErrorIdentifierRef
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorAction
//       //       }
//       //     }
//       //   },
//       //   {
//       //     {"System partitions HM table"}, // TableName
//       //     { // SystemError
//       //       { // ErrorAction
//       //         3, // ErrorIdentifierRef
//       //         ERROR_LEVEL_TYPE::MODULE, // ErrorLevel
//       //         {}, // ErrorAction
//       //       },
//       //       { // ErrorAction
//       //         4, // ErrorIdentifierRef
//       //         ERROR_LEVEL_TYPE::MODULE, // ErrorLevel
//       //         {}, // ErrorAction
//       //       },
//       //       { // ErrorAction
//       //         5, // ErrorIdentifierRef
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorAction
//       //       },
//       //       { // ErrorAction
//       //         6, // ErrorIdentifierRef
//       //         ERROR_LEVEL_TYPE::MODULE, // ErrorLevel
//       //         {}, // ErrorAction
//       //       },
//       //       { // ErrorAction
//       //         7, // ErrorIdentifierRef
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorAction
//       //       },
//       //       { // ErrorAction
//       //         8, // ErrorIdentifierRef
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorAction
//       //       },
//       //       { // ErrorAction
//       //         9, // ErrorIdentifierRef
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorAction
//       //       }
//       //     }
//       //   }
//       // },
//       // { // ModulesHM
//       //   { // ModuleHM
//       //     1, // StateIdentifier
//       //     {"module init"}, // Description
//       //     { // ErrorAction
//       //       { // ErrorAction
//       //         1, // ErrorIdentifierRef
//       //         MODULE_RECOVERY_ACTION_TYPE::SHUTDOWN, // ModuleRecoveryAction
//       //       },
//       //       { // ErrorAction
//       //         2, // ErrorIdentifierRef
//       //         MODULE_RECOVERY_ACTION_TYPE::SHUTDOWN, // ModuleRecoveryAction
//       //       },
//       //       { // ErrorAction
//       //         5, // ErrorIdentifierRef
//       //         MODULE_RECOVERY_ACTION_TYPE::SHUTDOWN, // ModuleRecoveryAction
//       //       },
//       //       { // ErrorAction
//       //         6, // ErrorIdentifierRef
//       //         MODULE_RECOVERY_ACTION_TYPE::IGNORE, // ModuleRecoveryAction
//       //       },
//       //       { // ErrorAction
//       //         7, // ErrorIdentifierRef
//       //         MODULE_RECOVERY_ACTION_TYPE::IGNORE, // ModuleRecoveryAction
//       //       }
//       //     }
//       //   },
//       //   { // ModuleHM
//       //     2, // StateIdentifier
//       //     {"system function execution"}, // Description
//       //     { // ErrorAction
//       //       { // ErrorAction
//       //         5, // ErrorIdentifierRef
//       //         MODULE_RECOVERY_ACTION_TYPE::SHUTDOWN, // ModuleRecoveryAction
//       //       },
//       //       { // ErrorAction
//       //         6, // ErrorIdentifierRef
//       //         MODULE_RECOVERY_ACTION_TYPE::IGNORE, // ModuleRecoveryAction
//       //       },
//       //       { // ErrorAction
//       //         7, // ErrorIdentifierRef
//       //         MODULE_RECOVERY_ACTION_TYPE::IGNORE, // ModuleRecoveryAction
//       //       },
//       //       { // ErrorAction
//       //         8, // ErrorIdentifierRef
//       //         MODULE_RECOVERY_ACTION_TYPE::IGNORE, // ModuleRecoveryAction
//       //       },
//       //       { // ErrorAction
//       //         9, // ErrorIdentifierRef
//       //         MODULE_RECOVERY_ACTION_TYPE::IGNORE, // ModuleRecoveryAction
//       //       }
//       //     }
//       //   }
//       // },
//       // { // PartitionHM
//       //   { // PartitionsHM
//       //     {"systemManagement HM table"}, // TableName
//       //     {"System partitions HM table"}, // MultiPartitionHMTableNameRef
//       //     { // SystemError
//       //       { // ErrorAction
//       //         5, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::IDLE, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PROCESS, // ErrorLevel
//       //         ERROR_CODE_TYPE::MEMORY_VIOLATION, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         7, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::IDLE, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PROCESS, // ErrorLevel
//       //         ERROR_CODE_TYPE::ILLEGAL_REQUEST, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         8, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::IDLE, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PROCESS, // ErrorLevel
//       //         ERROR_CODE_TYPE::NUMERIC_ERROR, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         9, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::IDLE, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PROCESS, // ErrorLevel
//       //         ERROR_CODE_TYPE::NUMERIC_ERROR, // ErrorCode
//       //       }
//       //     }
//       //   },
//       //   { // PartitionsHM
//       //     {"flightControls HM table"}, // TableName
//       //     {"Avionic partitions HM table"}, // MultiPartitionHMTableNameRef
//       //     { // SystemError
//       //       { // ErrorAction
//       //         3, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::IDLE, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         4, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::COLD_RESTART, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         5, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::IDLE, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PROCESS, // ErrorLevel
//       //         ERROR_CODE_TYPE::MEMORY_VIOLATION, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         6, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::WARM_RESTART, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PROCESS, // ErrorLevel
//       //         ERROR_CODE_TYPE::DEADLINE_MISSED, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         7, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::IDLE, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PROCESS, // ErrorLevel
//       //         ERROR_CODE_TYPE::ILLEGAL_REQUEST, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         8, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::IDLE, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PROCESS, // ErrorLevel
//       //         ERROR_CODE_TYPE::NUMERIC_ERROR, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         9, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::IDLE, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PROCESS, // ErrorLevel
//       //         ERROR_CODE_TYPE::NUMERIC_ERROR, // ErrorCode
//       //       }
//       //     }
//       //   },
//       //   { // PartitionsHM
//       //     {"flightManagement HM table"}, // TableName
//       //     {"Avionic partitions HM table"}, // MultiPartitionHMTableNameRef
//       //     { // SystemError
//       //       { // ErrorAction
//       //         3, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::IDLE, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         4, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::COLD_RESTART, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         5, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::IDLE, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PROCESS, // ErrorLevel
//       //         ERROR_CODE_TYPE::MEMORY_VIOLATION, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         6, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::WARM_RESTART, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PROCESS, // ErrorLevel
//       //         ERROR_CODE_TYPE::DEADLINE_MISSED, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         7, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::IDLE, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PROCESS, // ErrorLevel
//       //         ERROR_CODE_TYPE::ILLEGAL_REQUEST, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         8, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::IDLE, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PROCESS, // ErrorLevel
//       //         ERROR_CODE_TYPE::NUMERIC_ERROR, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         9, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::IDLE, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PROCESS, // ErrorLevel
//       //         ERROR_CODE_TYPE::NUMERIC_ERROR, // ErrorCode
//       //       }
//       //     }
//       //   },
//       //   { // PartitionsHM
//       //     {"IO processing HM table"}, // TableName
//       //     {"Avionic partitions HM table"}, // MultiPartitionHMTableNameRef
//       //     { // SystemError
//       //       { // ErrorAction
//       //         3, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::IDLE, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         4, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::COLD_RESTART, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         5, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::IDLE, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PROCESS, // ErrorLevel
//       //         ERROR_CODE_TYPE::MEMORY_VIOLATION, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         6, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::WARM_RESTART, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PROCESS, // ErrorLevel
//       //         ERROR_CODE_TYPE::DEADLINE_MISSED, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         7, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::IDLE, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PROCESS, // ErrorLevel
//       //         ERROR_CODE_TYPE::ILLEGAL_REQUEST, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         8, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::COLD_RESTART, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         9, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::COLD_RESTART, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorCode
//       //       }
//       //     }
//       //   },
//       //   { // PartitionHM
//       //     {"IHVM HM table"}, // TableName
//       //     {"Avionic partitions HM table"}, // MultiPartitionHMTableNameRef
//       //     { // SystemError
//       //       { // ErrorAction
//       //         3, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::IDLE, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         4, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::COLD_RESTART, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         5, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::IDLE, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PROCESS, // ErrorLevel
//       //         ERROR_CODE_TYPE::MEMORY_VIOLATION, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         6, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::IDLE, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         7, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::IDLE, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         8, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::IDLE, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorCode
//       //       },
//       //       { // ErrorAction
//       //         9, // ErrorIdentifierRef
//       //         PARTITION_RECOVERY_ACTION_TYPE::IDLE, // PartitionRecoveryAction
//       //         ERROR_LEVEL_TYPE::PARTITION, // ErrorLevel
//       //         {}, // ErrorCode
//       //       }
//       //     }
//       //   }
//       // }
    };
//
//   //ErrorLevel eL = {1, NAME_TYPE{""}, ERROR_LEVEL_TYPE::MODULE, ERROR_CODE_TYPE::DEADLINE_MISSED};
//
//   //SystemHMTable sHM {3, { {1, NAME_TYPE{""}, 1, { {1, NAME_TYPE{""}, ErrorLevelType::MODULE, ErrorCodeType::DEADLINE_MISSED} }, 1, { {1, NAME_TYPE{""}, ModuleActionType::IGNORE} }}}};
     //SystemStateEntry(2, {}, 1, [ErrorLevel(2, {}, ErrorLevelType::MODULE, {})], 1, [ErrorAction(2, {}, ModuleActionType::IGNORE)]),
     //SystemStateEntry(3, {}, 1, [ErrorLevel(3, {}, ErrorLevelType::MODULE, {})], 1, [ErrorAction(3, {}, ModuleActionType::IGNORE)])]);


  return 0;
}
