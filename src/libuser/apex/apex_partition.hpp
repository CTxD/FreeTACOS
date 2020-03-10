/*----------------------------------------------------------------*/
/*                                                                */
/* PARTITION constant and type definitions and management services*/
/*                                                                */
/*----------------------------------------------------------------*/

#ifndef APEX_PARTITION
#define APEX_PARTITION

#include "apex_process.h"

#define MAX_NUMBER_OF_PARTITIONS SYSTEM_LIMIT_NUMBER_OF_PARTITIONS

typedef enum {
    IDLE = 0,
    COLD_START = 1,
    WARM_START = 2,
    NORMAL = 3
} OPERATING_MODE_TYPE;

typedef APEX_INTEGER PARTITION_ID_TYPE;

typedef APEX_UNSIGNED NUM_CORES_TYPE;

enum START_CONDITION_TYPE {
    NORMAL_START = 0,
    PARTITION_RESTART = 1,
    HM_MODULE_RESTART = 2,
    HM_PARTITION_RESTART = 3
};

typedef enum {
    LEVEL_A = 0,
    LEVEL_B = 1,
    LEVEL_C = 2,
    LEVEL_D = 3,
    LEVEL_E = 4
} CRITICALITY_TYPE;

struct PARTITION_STATUS_TYPE {
    PARTITION_ID_TYPE IDENTIFIER;
    NUM_CORES_TYPE NUM_ASSIGNED_CORES;
    SYSTEM_TIME_TYPE DURATION;
    SYSTEM_TIME_TYPE PERIOD;
    LOCK_LEVEL_TYPE LOCK_LEVEL;
    OPERATING_MODE_TYPE OPERATING_MODE;
    START_CONDITION_TYPE START_CONDITION;

    PARTITION_STATUS_TYPE(){};

    PARTITION_STATUS_TYPE(PARTITION_ID_TYPE id,
                          NUM_CORES_TYPE affinity,
                          SYSTEM_TIME_TYPE duration,
                          SYSTEM_TIME_TYPE period)
        : IDENTIFIER(id), NUM_ASSIGNED_CORES(affinity), DURATION(duration), PERIOD(period)
    {
        this->LOCK_LEVEL = 0;
        this->OPERATING_MODE = OPERATING_MODE_TYPE::COLD_START;
        this->START_CONDITION = START_CONDITION_TYPE::NORMAL_START;
    }
};

enum class PARTITION_RECOVERY_ACTION_TYPE {
    IGNORE = 0,
    IDLE = 1,
    WARM_RESTART = 2,
    COLD_RESTART = 3
};

extern void GET_PARTITION_STATUS(
    /*out*/ PARTITION_STATUS_TYPE* PARTITION_STATUS,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

extern void SET_PARTITION_MODE(
    /*in */ OPERATING_MODE_TYPE OPERATING_MODE,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

#endif
