/*-------------------------------------------------------------------*/
/*                                                                   */
/* BLACKBOARD constant and type definitions and management services  */
/*                                                                   */
/*-------------------------------------------------------------------*/

#ifndef APEX_BLACKBOARD
#define APEX_BLACKBOARD

#include "apex_process.hpp"
#include "apex_types.hpp"

#define MAX_NUMBER_OF_BLACKBOARDS SYSTEM_LIMIT_NUMBER_OF_BLACKBOARDS

typedef NAME_TYPE BLACKBOARD_NAME_TYPE;

typedef APEX_INTEGER BLACKBOARD_ID_TYPE;
typedef enum { EMPTY = 0, OCCUPIED = 1 } EMPTY_INDICATOR_TYPE;

typedef struct {
    EMPTY_INDICATOR_TYPE EMPTY_INDICATOR;
    MESSAGE_SIZE_TYPE MAX_MESSAGE_SIZE;
    WAITING_RANGE_TYPE WAITING_PROCESSES;
} BLACKBOARD_STATUS_TYPE;

extern void CREATE_BLACKBOARD(
    /*in */ BLACKBOARD_NAME_TYPE BLACKBOARD_NAME,
    /*in */ MESSAGE_SIZE_TYPE MAX_MESSAGE_SIZE,
    /*out*/ BLACKBOARD_ID_TYPE* BLACKBOARD_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

extern void DISPLAY_BLACKBOARD(
    /*in */ BLACKBOARD_ID_TYPE BLACKBOARD_ID,
    /*in */ MESSAGE_ADDR_TYPE MESSAGE_ADDR, /* by reference */
    /*in */ MESSAGE_SIZE_TYPE LENGTH,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

extern void READ_BLACKBOARD(
    /*in */ BLACKBOARD_ID_TYPE BLACKBOARD_ID,
    /*in */ SYSTEM_TIME_TYPE TIME_OUT,
    /*out*/ MESSAGE_ADDR_TYPE MESSAGE_ADDR,
    /*out*/ MESSAGE_SIZE_TYPE* LENGTH,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

extern void CLEAR_BLACKBOARD(
    /*in */ BLACKBOARD_ID_TYPE BLACKBOARD_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

extern void GET_BLACKBOARD_ID(
    /*in */ BLACKBOARD_NAME_TYPE BLACKBOARD_NAME,
    /*out*/ BLACKBOARD_ID_TYPE* BLACKBOARD_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

extern void GET_BLACKBOARD_STATUS(
    /*in */ BLACKBOARD_ID_TYPE BLACKBOARD_ID,
    /*out*/ BLACKBOARD_STATUS_TYPE* BLACKBOARD_STATUS,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

#endif
