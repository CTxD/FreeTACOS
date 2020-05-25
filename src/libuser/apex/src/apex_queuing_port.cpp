#include "arinc_module.hpp"
#include <apex_queuing_port.hpp>
#include <circle/logger.h>

std::vector<QueuingPortType*> ApexQueuingPort::ports = {};
bool ApexQueuingPort::initialised = false;

void ApexQueuingPort::CREATE_QUEUING_PORT(
    /*in */ QUEUING_PORT_NAME_TYPE QUEUING_PORT_NAME,
    /*in */ MESSAGE_SIZE_TYPE MAX_MESSAGE_SIZE,
    /*in */ MESSAGE_RANGE_TYPE MAX_NB_MESSAGE,
    /*in */ PORT_DIRECTION_TYPE PORT_DIRECTION,
    /*in */ QUEUING_DISCIPLINE_TYPE QUEUING_DISCIPLINE,
    /*out*/ QUEUING_PORT_ID_TYPE* QUEUING_PORT_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    assert(initialised && "Queuing Ports must be initialised before use");

    // Create status
    QUEUING_PORT_STATUS_TYPE status = {0, MAX_NB_MESSAGE, MAX_MESSAGE_SIZE,
                                       PORT_DIRECTION, 0};

    bool found = false;
    QUEUING_PORT_ID_TYPE id;

    // Find queuing port by name
    for (auto& port : ports) {
        if (*port->name.x == *QUEUING_PORT_NAME.x) {
            // Update port
            port->status = new QUEUING_PORT_STATUS_TYPE{
                0, MAX_NB_MESSAGE, MAX_MESSAGE_SIZE, PORT_DIRECTION, 0};
            port->discipline = QUEUING_DISCIPLINE;
            id = port->id;

            found = true;
            break;
        }
    }

    // Check if it was found
    if (!found) {
        *RETURN_CODE = INVALID_PARAM;
        return;
    }

    // Averything went well
    *RETURN_CODE = NO_ERROR;
    *QUEUING_PORT_ID = id;
}

void ApexQueuingPort::SEND_QUEUING_MESSAGE(
    /*in */ QUEUING_PORT_ID_TYPE QUEUING_PORT_ID,
    /*in */ MESSAGE_ADDR_TYPE MESSAGE_ADDR, /* by reference */
    /*in */ MESSAGE_SIZE_TYPE LENGTH,
    /*in */ SYSTEM_TIME_TYPE TIME_OUT,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    // TODO: Implement timeout
    QueuingPortType* aPort = nullptr;
    CLogger::Get()->Write("Debugger", LogNotice, "This Far 0");
    // Find queuing port
    for (auto& port : ports) {
        if (port->id == QUEUING_PORT_ID) {
            // Check message length
            if (LENGTH > port->status->MAX_MESSAGE_SIZE) {
                *RETURN_CODE = INVALID_CONFIG;
                return;
            }
            CLogger::Get()->Write("Debugger", LogNotice, "This Far 1");
            aPort = port;
        }
    }

    CLogger::Get()->Write("Debugger", LogNotice, "This Far 2");
    if (aPort = nullptr) {
        *RETURN_CODE = INVALID_PARAM;
        return;
    }

    CLogger::Get()->Write("Debugger", LogNotice, "This Far 3");
    // Update port and return;
    // aPort->messages.push_back(MESSAGE_ADDR);
    CLogger::Get()->Write("Debugger", LogNotice, "This Far 4");
    aPort->status->NB_MESSAGE++;

    CLogger::Get()->Write("Debugger", LogNotice, "This Far 5");
    *RETURN_CODE = NO_ERROR;
}

void ApexQueuingPort::RECEIVE_QUEUING_MESSAGE(
    /*in */ QUEUING_PORT_ID_TYPE QUEUING_PORT_ID,
    /*in */ SYSTEM_TIME_TYPE TIME_OUT,
    /*out*/ MESSAGE_ADDR_TYPE* MESSAGE_ADDR,
    /*out*/ MESSAGE_SIZE_TYPE* LENGTH,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    // TODO: Implement timeout
    QueuingPortType* aPort = nullptr;

    // Find queuing port
    for (auto& port : ports) {
        if (port->id == QUEUING_PORT_ID) {
            if (port->status->MAX_NB_MESSAGE <= 0) {
                *RETURN_CODE = NOT_AVAILABLE;
            }
            aPort = port;
        }
    }

    if (aPort = nullptr) {
        *RETURN_CODE = INVALID_PARAM;
        return;
    }

    // Find message and return
    *MESSAGE_ADDR = aPort->messages.back();
    aPort->messages.pop_back();

    *RETURN_CODE = NO_ERROR;
}

void ApexQueuingPort::GET_QUEUING_PORT_ID(
    /*in */ QUEUING_PORT_NAME_TYPE QUEUING_PORT_NAME,
    /*out*/ QUEUING_PORT_ID_TYPE* QUEUING_PORT_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    QueuingPortType* aPort = nullptr;

    // Find queuing port
    for (auto& port : ports) {
        if (*port->name.x == *QUEUING_PORT_NAME.x) {
            aPort = port;
        }
    }

    if (aPort = nullptr) {
        *RETURN_CODE = INVALID_PARAM;
        return;
    }

    *QUEUING_PORT_ID = aPort->id;
    *RETURN_CODE = NO_ERROR;
}

void ApexQueuingPort::GET_QUEUING_PORT_STATUS(
    /*in */ QUEUING_PORT_ID_TYPE QUEUING_PORT_ID,
    /*out*/ QUEUING_PORT_STATUS_TYPE* QUEUING_PORT_STATUS,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    QueuingPortType* aPort = nullptr;

    // Find queuing port
    for (auto& port : ports) {
        if (port->id == QUEUING_PORT_ID) {
            if (port->status->MAX_NB_MESSAGE <= 0) {
                *RETURN_CODE = NOT_AVAILABLE;
            }
            aPort = port;
        }
    }

    if (aPort = nullptr) {
        *RETURN_CODE = INVALID_PARAM;
        return;
    }

    QUEUING_PORT_STATUS = aPort->status;
    *RETURN_CODE = NO_ERROR;
}

void ApexQueuingPort::CLEAR_QUEUING_PORT(
    /*in */ QUEUING_PORT_ID_TYPE QUEUING_PORT_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    QueuingPortType* aPort = nullptr;

    // Find queuing port
    for (auto& port : ports) {
        if (port->id == QUEUING_PORT_ID) {
            if (port->status->MAX_NB_MESSAGE <= 0) {
                *RETURN_CODE = NOT_AVAILABLE;
            }
            aPort = port;
        }
    }

    if (aPort = nullptr) {
        *RETURN_CODE = INVALID_PARAM;
        return;
    }

    // Clear all messages
    aPort->status->NB_MESSAGE = 0;
    aPort->messages = {};

    *RETURN_CODE = NO_ERROR;
}

void ApexQueuingPort::initialiseQueues()
{
    // Initialise all queues from all partitions
    for (auto& partition : ArincModule::generatedArincModule.partitions) {
        for (auto& port : partition.getQueuePorts()) {
            // Initialise ports
            ports.push_back(new QueuingPortType{
                ports.size(), port.portName, QUEUING_DISCIPLINE_TYPE::FIFO,
                new QUEUING_PORT_STATUS_TYPE{0, port.getMaxNumMessages(),
                                             port.maxMessageSize, port.direction, 0},
                std::vector<MESSAGE_ADDR_TYPE>{}});
        }
    }

    // Set initialised true
    initialised = true;
}