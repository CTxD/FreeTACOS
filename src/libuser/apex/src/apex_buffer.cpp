#include "apex_buffer.hpp"
#include "partitionscheduling.hpp"
#include <arinc_module.hpp>

std::vector<PartitionBuffer> ApexBuffer::partitionBuffers{};
bool ApexBuffer::initialised = false;

/**
 * @brief Create a buffer for interpartition communication
 *
 * @param BUFFER_NAME
 * @param MAX_MESSAGE_SIZE
 * @param MAX_NB_MESSAGE
 * @param QUEUING_DISCIPLINE
 * @param BUFFER_ID
 * @param RETURN_CODE
 */
void ApexBuffer::CREATE_BUFFER(
    /*in */ BUFFER_NAME_TYPE BUFFER_NAME,
    /*in */ MESSAGE_SIZE_TYPE MAX_MESSAGE_SIZE,
    /*in */ MESSAGE_RANGE_TYPE MAX_NB_MESSAGE,
    /*in */ QUEUING_DISCIPLINE_TYPE QUEUING_DISCIPLINE,
    /*out*/ BUFFER_ID_TYPE* BUFFER_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    assert(initialised && "Buffers must be initialised before use");

    auto* currentPartition = CyclicExecutiveSchedule::getCurrentPartition();

    for (auto& partitionBuffer : partitionBuffers) {
        // Find the right partition
        if (*currentPartition->partitionName.x == partitionBuffer.partitionName) {
            // Check if buffer already exist
            for (auto& buffer : partitionBuffer.buffers) {
                if (*buffer.bufferName.x == *BUFFER_NAME.x) {
                    *RETURN_CODE = INVALID_PARAM;
                    return;
                }
            }

            // Create buffer
            partitionBuffer.buffers.push_back(
                {BUFFER_NAME, QUEUING_DISCIPLINE, {{}, MAX_NB_MESSAGE, MAX_MESSAGE_SIZE, {}}});

            *BUFFER_ID = partitionBuffer.buffers.size() - 1;
            *RETURN_CODE = NO_ERROR;
            return;
        }
    }

    *RETURN_CODE = NOT_AVAILABLE;
    *BUFFER_ID = -1;
}

/**
 * @brief Populate a buffer with a message
 *
 * @param BUFFER_ID
 * @param MESSAGE_ADDR
 * @param LENGTH
 * @param TIME_OUT
 * @param RETURN_CODE
 */
void ApexBuffer::SEND_BUFFER(
    /*in */ BUFFER_ID_TYPE BUFFER_ID,
    /*in */ MESSAGE_ADDR_TYPE MESSAGE_ADDR, /* by reference */
    /*in */ MESSAGE_SIZE_TYPE LENGTH,
    /*in */ SYSTEM_TIME_TYPE TIME_OUT,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    // TODO: CREATE TIMER FOR TIMEOUT

    auto* currentPartition = CyclicExecutiveSchedule::getCurrentPartition();
    for (auto& partitionBuffer : partitionBuffers) {
        // Find partitionBuffer
        if (*currentPartition->partitionName.x == partitionBuffer.partitionName) {
            auto& buffers = partitionBuffer.buffers;
            if (buffers.size() < BUFFER_ID + 1 ||
                buffers.at(BUFFER_ID).buffer.MAX_MESSAGE_SIZE < LENGTH) {
                *RETURN_CODE = INVALID_PARAM;
                return;
            }

            // Send buffer
            buffers.at(BUFFER_ID).buffer.NB_MESSAGE = MESSAGE_ADDR;

            *RETURN_CODE = NO_ERROR;
            return;
        }
    }

    *RETURN_CODE = NOT_AVAILABLE;
}

/**
 * @brief Recieve a message from a buffer
 *
 * @param BUFFER_ID
 * @param TIME_OUT
 * @param MESSAGE_ADDR
 * @param LENGTH
 * @param RETURN_CODE
 */
void ApexBuffer::RECEIVE_BUFFER(
    /*in */ BUFFER_ID_TYPE BUFFER_ID,
    /*in */ SYSTEM_TIME_TYPE TIME_OUT,
    /*out*/ MESSAGE_ADDR_TYPE* MESSAGE_ADDR,
    /*out*/ MESSAGE_SIZE_TYPE* LENGTH,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    auto* currentPartition = CyclicExecutiveSchedule::getCurrentPartition();

    for (auto& partitionBuffer : partitionBuffers) {
        // Find buffer
        if (partitionBuffer.partitionName == *currentPartition->partitionName.x) {
            auto& buffers = partitionBuffer.buffers;
            if (partitionBuffer.buffers.size() < BUFFER_ID + 1) {
                *RETURN_CODE = INVALID_PARAM;
                return;
            }

            *MESSAGE_ADDR = buffers.at(BUFFER_ID).buffer.NB_MESSAGE;
            *LENGTH = buffers.at(BUFFER_ID).buffer.MAX_MESSAGE_SIZE;
            *RETURN_CODE = NO_ERROR;
            return;
        }
    }

    *RETURN_CODE = NOT_AVAILABLE;
}

/**
 * @brief Get the id of a buffer by name
 *
 * @param BUFFER_NAME
 * @param BUFFER_ID
 * @param RETURN_CODE
 */
void ApexBuffer::GET_BUFFER_ID(
    /*in */ BUFFER_NAME_TYPE BUFFER_NAME,
    /*out*/ BUFFER_ID_TYPE* BUFFER_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    auto* currentPartition = CyclicExecutiveSchedule::getCurrentPartition();

    for (auto& partitionBuffer : partitionBuffers) {
        // Find buffer
        if (partitionBuffer.partitionName == *currentPartition->partitionName.x) {
            auto id = 0;
            for (auto& buffer : partitionBuffer.buffers) {
                if (*buffer.bufferName.x == *BUFFER_NAME.x) {
                    *BUFFER_ID = id;
                    *RETURN_CODE = NO_ERROR;
                    return;
                }
                id++;
            }
        }
    }

    *RETURN_CODE = NO_ERROR;
    return;
}

/**
 * @brief Get the status of a buffer by id
 *
 * @param BUFFER_ID
 * @param BUFFER_STATUS
 * @param RETURN_CODE
 */
void ApexBuffer::GET_BUFFER_STATUS(
    /*in */ BUFFER_ID_TYPE BUFFER_ID,
    /*out*/ BUFFER_STATUS_TYPE* BUFFER_STATUS,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    auto* currentPartition = CyclicExecutiveSchedule::getCurrentPartition();

    for (auto& partitionBuffer : partitionBuffers) {
        // Find buffer
        if (partitionBuffer.partitionName == *currentPartition->partitionName.x) {
            auto& buffers = partitionBuffer.buffers;
            if (partitionBuffer.buffers.size() < BUFFER_ID + 1) {
                *RETURN_CODE = INVALID_PARAM;
                return;
            }

            *BUFFER_STATUS = buffers.at(BUFFER_ID).buffer;
            *RETURN_CODE = NO_ERROR;
            return;
        }
    }

    *RETURN_CODE = NOT_AVAILABLE;
}

/**
 * @brief Initialise partition buffers. This must be done before using the buffer
 *
 */
void ApexBuffer::initialiseBuffers()
{
    auto& module = ArincModule::generatedArincModule;

    for (auto& partition : module.partitions) {
        partitionBuffers.push_back({*partition.getPartitionName().x.x, {}});
    }

    initialised = true;
}