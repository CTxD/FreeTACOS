/*----------------------------------------------------------------*/
/*                                                                */
/* TIME constant and type definitions and management services     */
/*                                                                */
/*----------------------------------------------------------------*/

#ifndef APEX_TIME
#define APEX_TIME

#include "apex_types.hpp"

class Time {
public:
    static void TIMED_WAIT(
        /*in */ SYSTEM_TIME_TYPE DELAY_TIME,
        /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

    static void PERIODIC_WAIT(
        /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

    static void GET_TIME(
        /*out*/ SYSTEM_TIME_TYPE* SYSTEM_TIME,
        /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

    static void REPLENISH(
        /*in */ SYSTEM_TIME_TYPE BUDGET_TIME,
        /*out*/ RETURN_CODE_TYPE* RETURN_CODE);
};

#endif
