/*-------------------------------------------------------------------*/
/*                                                                   */
/* MUTEX constant and type definitions and management services       */
/*                                                                   */
/*-------------------------------------------------------------------*/

#ifndef APEX_MUTEX
#define APEX_MUTEX

#include "apex_process.hpp"
#include "apex_types.hpp"
#include <vector>
#include <queue>

#define MAX_NUMBER_OF_MUTEXES SYSTEM_LIMIT_NUMBER_OF_MUTEXES

typedef NAME_TYPE MUTEX_NAME_TYPE;

typedef APEX_INTEGER MUTEX_ID_TYPE;

#define NO_MUTEX_OWNED -2

#define PREEMPTION_LOCK_MUTEX -3

typedef APEX_INTEGER LOCK_COUNT_TYPE;

typedef enum { AVAILABLE = 0, OWNED = 1 } MUTEX_STATE_TYPE;

typedef struct {
    PROCESS_ID_TYPE MUTEX_OWNER;
    MUTEX_STATE_TYPE MUTEX_STATE;
    PRIORITY_TYPE MUTEX_PRIORITY;
    LOCK_COUNT_TYPE LOCK_COUNT;
    WAITING_RANGE_TYPE WAITING_PROCESSES;
} MUTEX_STATUS_TYPE;

typedef std::queue<MUTEX_ID_TYPE> WaitingProcesses;
typedef struct {
    MUTEX_NAME_TYPE mutexName;
    MUTEX_ID_TYPE mutexId;
    QUEUING_DISCIPLINE_TYPE queingDiscipline;
    MUTEX_STATUS_TYPE mutex;
    WaitingProcesses waitingProcesses;
} Mutex;

typedef std::vector<Mutex> MutexVector;
typedef struct {
    const char* partitionName;
    MutexVector mutexes;
} PartitionMutex;

class ApexMutex{
private:
    static int getMutexAmount();
    static std::vector<PartitionMutex> partitionMutexes;
public:
static void CREATE_MUTEX(
    /*in */ MUTEX_NAME_TYPE MUTEX_NAME,
    /*in */ PRIORITY_TYPE MUTEX_PRIORITY,
    /*in */ QUEUING_DISCIPLINE_TYPE QUEUING_DISCIPLINE,
    /*out*/ MUTEX_ID_TYPE MUTEX_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

static void ACQUIRE_MUTEX(
    /*in */ MUTEX_ID_TYPE MUTEX_ID,
    /*in */ SYSTEM_TIME_TYPE TIME_OUT,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

static void RELEASE_MUTEX(
    /*in */ MUTEX_ID_TYPE MUTEX_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

static void RESET_MUTEX(
    /*in */ MUTEX_ID_TYPE MUTEX_ID,
    /*in */ PROCESS_ID_TYPE PROCESS_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

static void GET_MUTEX_ID(
    /*in */ MUTEX_NAME_TYPE MUTEX_NAME,
    /*in */ MUTEX_ID_TYPE MUTEX_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

static void GET_MUTEX_STATUS(
    /*in */ MUTEX_ID_TYPE MUTEX_ID,
    /*out*/ MUTEX_STATUS_TYPE MUTEX_STATUS,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

// TODO: Implement for health monitor
static void GET_PROCESS_MUTEX_STATE(
    /*in */ PROCESS_ID_TYPE PROCESS_ID,
    /*out*/ MUTEX_ID_TYPE MUTEX_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE);
};

#endif
