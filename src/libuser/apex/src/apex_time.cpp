#include <apex_time.hpp>
#include <circle/timer.h>

void Time::TIMED_WAIT(
    /*in */ SYSTEM_TIME_TYPE DELAY_TIME,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
}

void PERIODIC_WAIT(
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
}

void Time::GET_TIME(
    /*out*/ SYSTEM_TIME_TYPE* SYSTEM_TIME,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    SYSTEM_TIME_TYPE currentTime = CTimer::Get()->GetClockTicks();

    *SYSTEM_TIME = currentTime;
    *RETURN_CODE = NO_ERROR;
}

void REPLENISH(
    /*in */ SYSTEM_TIME_TYPE BUDGET_TIME,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
}