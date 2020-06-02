#include <apex_queuing_port.hpp>
#include <arinc_module.hpp>
#include <circle/logger.h>
#include <partitionscheduling.hpp>

std::vector<PartitionPort> ApexQueuingPort::partitionPorts = {};
std::vector<PortType*> ApexQueuingPort::ports = {};

void ApexQueuingPort::CREATE_QUEUING_PORT(
    /*in */ QUEUING_PORT_NAME_TYPE QUEUING_PORT_NAME,
    /*in */ MESSAGE_SIZE_TYPE MAX_MESSAGE_SIZE,
    /*in */ MESSAGE_RANGE_TYPE MAX_NB_MESSAGE,
    /*in */ PORT_DIRECTION_TYPE PORT_DIRECTION,
    /*in */ QUEUING_DISCIPLINE_TYPE QUEUING_DISCIPLINE,
    /*out*/ QUEUING_PORT_ID_TYPE* QUEUING_PORT_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    auto& partName =
        *CyclicExecutiveSchedule::GetCurrentPartition()->partitionName.x;

    bool partFound = false;

    QUEUING_PORT_ID_TYPE id;

    // Find partition queue
    for (auto& partition : partitionPorts) {
        if (*partition.name.x.x == partName) {
            // Check if port already exist
            for (auto& port : partition.ports) {
                if (*port->name.x == *QUEUING_PORT_NAME.x) {
                    *RETURN_CODE = NOT_AVAILABLE;
                    break;
                }
            }

            PortType* queue = nullptr;
            // Check if message queue exist
            for (auto* port : ports) {
                if (*port->name.x == *QUEUING_PORT_NAME.x) {
                    queue = port;
                    break;
                }
            }

            // If doesn't exist, create it
            if (queue == nullptr) {
                ports.push_back(new PortType{QUEUING_PORT_NAME, {}});
                queue = ports.back();
            }

            // Create a new queue
            partition.ports.push_back(new QueuingPortType{
                QUEUING_PORT_NAME,
                QUEUING_DISCIPLINE,
                {0, MAX_NB_MESSAGE, MAX_MESSAGE_SIZE, PORT_DIRECTION, 0},
                queue});

            id = partition.ports.size() - 1;

            partFound = true;
            break;
        }
    }

    // If no partition were founf
    if (!partFound) {
        *RETURN_CODE = INVALID_PARAM;
        return;
    }

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
    auto& partName =
        *CyclicExecutiveSchedule::GetCurrentPartition()->partitionName.x;

    // Find partition
    for (auto& partition : partitionPorts) {
        if (*partition.name.x.x == partName) {
            // Check if queue exist and if it is a source
            if (partition.ports.size() - 1 < QUEUING_PORT_ID) {
                *RETURN_CODE = INVALID_PARAM;
                return;
            }
            else if (partition.ports.at(QUEUING_PORT_ID)->status.PORT_DIRECTION == DESTINATION) {
                *RETURN_CODE = NOT_AVAILABLE;
            }

            // Push message to queue
            partition.ports.at(QUEUING_PORT_ID)->port->messages.push_back(MESSAGE_ADDR);
            break;
        }
    }

    // No error
    *RETURN_CODE = NO_ERROR;
}

void ApexQueuingPort::RECEIVE_QUEUING_MESSAGE(
    /*in */ QUEUING_PORT_ID_TYPE QUEUING_PORT_ID,
    /*in */ SYSTEM_TIME_TYPE TIME_OUT,
    /*out*/ MESSAGE_ADDR_TYPE* MESSAGE_ADDR,
    /*out*/ MESSAGE_SIZE_TYPE* LENGTH,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    auto& partName =
        *CyclicExecutiveSchedule::GetCurrentPartition()->partitionName.x;

    // Find partition
    for (auto& partition : partitionPorts) {
        if (*partition.name.x.x == partName) {
            // Check if the queue exist && check if there is any messages
            if (partition.ports.size() - 1 < QUEUING_PORT_ID) {
                *RETURN_CODE = INVALID_PARAM;
                return;
            }

            // Check if there are any messages in the queue
            if (partition.ports.at(QUEUING_PORT_ID)->port->messages.size() == 0) {
                *RETURN_CODE = NOT_AVAILABLE;
                return;
            }

            // Push message to queue
            *MESSAGE_ADDR = partition.ports.at(QUEUING_PORT_ID)->port->messages.back();
            partition.ports.at(QUEUING_PORT_ID)->port->messages.pop_back();
            *RETURN_CODE = NO_ERROR;
            return;
        }
    }

    *RETURN_CODE = NOT_AVAILABLE;
}

void ApexQueuingPort::GET_QUEUING_PORT_ID(
    /*in */ QUEUING_PORT_NAME_TYPE QUEUING_PORT_NAME,
    /*out*/ QUEUING_PORT_ID_TYPE* QUEUING_PORT_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    for (auto& partPort : partitionPorts) {
        if (*partPort.name.x.x ==
            *CyclicExecutiveSchedule::GetCurrentPartition()->partitionName.x) {
        }
    }
}

void ApexQueuingPort::GET_QUEUING_PORT_STATUS(
    /*in */ QUEUING_PORT_ID_TYPE QUEUING_PORT_ID,
    /*out*/ QUEUING_PORT_STATUS_TYPE* QUEUING_PORT_STATUS,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
}

void ApexQueuingPort::CLEAR_QUEUING_PORT(
    /*in */ QUEUING_PORT_ID_TYPE QUEUING_PORT_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
}

bool ApexQueuingPort::initialised = false;

/**
 * @brief Initialise all queuing ports for each partition
 *
 */
void ApexQueuingPort::Initialise()
{
    // Get partitions and declarations
    auto& partitions = ArincModule::generatedArincModule.partitions;
    std::vector<QueuingPortType*> qPorts;
    std::vector<QueuingPort> ports;

    for (auto& partition : partitions) {
        // Retrieve all ports per partition
        ports = partition.getQueuePorts();
        qPorts = {};

        for (auto& port : ports) {
            // Create port
            // QUEUING_PORT_STATUS_TYPE status = {0, port.getMaxNumMessages(),
            //                                    port.getMaxMessageSize(),
            //                                    port.getDirection(), 0};

            // qPorts.push_back({status, {}});
        }

        // Push port
        partitionPorts.push_back({partition.getPartitionName(), qPorts});
    }

    // Set queuing ports to be initialised
    initialised = true;
}
