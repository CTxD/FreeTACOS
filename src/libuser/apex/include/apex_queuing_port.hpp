/*--------------------------------------------------------------------*/
/*                                                                    */
/* QUEUING PORT constant and type definitions and management services */
/*                                                                    */
/*--------------------------------------------------------------------*/
#ifndef APEX_QUEUING
#define APEX_QUEUING

#include "apex_process.hpp"
#include "apex_types.hpp"
#include "general_types.hpp"

#include <vector>

#define MAX_NUMBER_OF_QUEUING_PORTS SYSTEM_LIMIT_NUMBER_OF_QUEUING_PORTS

typedef NAME_TYPE QUEUING_PORT_NAME_TYPE;
typedef APEX_INTEGER QUEUING_PORT_ID_TYPE;

typedef struct {
    MESSAGE_RANGE_TYPE NB_MESSAGE;
    MESSAGE_RANGE_TYPE MAX_NB_MESSAGE;
    MESSAGE_SIZE_TYPE MAX_MESSAGE_SIZE;
    PORT_DIRECTION_TYPE PORT_DIRECTION;
    WAITING_RANGE_TYPE WAITING_PROCESSES;
} QUEUING_PORT_STATUS_TYPE;

typedef struct {
    QUEUING_PORT_NAME_TYPE name;
    std::vector<MESSAGE_ADDR_TYPE> messages;
} PortType;

typedef struct {
    QUEUING_PORT_NAME_TYPE name;
    QUEUING_DISCIPLINE_TYPE discipline;
    QUEUING_PORT_STATUS_TYPE status;
    PortType* port;
} QueuingPortType;

typedef struct {
    name_t name;
    std::vector<QueuingPortType*> ports;
} PartitionPort;

class ApexQueuingPort {
private:
    static bool initialised;
    static std::vector<PartitionPort> partitionPorts;
    static std::vector<PortType*> ports;

public:
    static void Initialise();
    static void CREATE_QUEUING_PORT(
        /*in */ QUEUING_PORT_NAME_TYPE QUEUING_PORT_NAME,
        /*in */ MESSAGE_SIZE_TYPE MAX_MESSAGE_SIZE,
        /*in */ MESSAGE_RANGE_TYPE MAX_NB_MESSAGE,
        /*in */ PORT_DIRECTION_TYPE PORT_DIRECTION,
        /*in */ QUEUING_DISCIPLINE_TYPE QUEUING_DISCIPLINE,
        /*out*/ QUEUING_PORT_ID_TYPE* QUEUING_PORT_ID,
        /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

    static void SEND_QUEUING_MESSAGE(
        /*in */ QUEUING_PORT_ID_TYPE QUEUING_PORT_ID,
        /*in */ MESSAGE_ADDR_TYPE MESSAGE_ADDR, /* by reference */
        /*in */ MESSAGE_SIZE_TYPE LENGTH,
        /*in */ SYSTEM_TIME_TYPE TIME_OUT,
        /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

    static void RECEIVE_QUEUING_MESSAGE(
        /*in */ QUEUING_PORT_ID_TYPE QUEUING_PORT_ID,
        /*in */ SYSTEM_TIME_TYPE TIME_OUT,
        /*out*/ MESSAGE_ADDR_TYPE* MESSAGE_ADDR,
        /*out*/ MESSAGE_SIZE_TYPE* LENGTH,
        /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

    static void GET_QUEUING_PORT_ID(
        /*in */ QUEUING_PORT_NAME_TYPE QUEUING_PORT_NAME,
        /*out*/ QUEUING_PORT_ID_TYPE* QUEUING_PORT_ID,
        /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

    static void GET_QUEUING_PORT_STATUS(
        /*in */ QUEUING_PORT_ID_TYPE QUEUING_PORT_ID,
        /*out*/ QUEUING_PORT_STATUS_TYPE* QUEUING_PORT_STATUS,
        /*out*/ RETURN_CODE_TYPE* RETURN_CODE);

    static void CLEAR_QUEUING_PORT(
        /*in */ QUEUING_PORT_ID_TYPE QUEUING_PORT_ID,
        /*out*/ RETURN_CODE_TYPE* RETURN_CODE);
};

#endif
