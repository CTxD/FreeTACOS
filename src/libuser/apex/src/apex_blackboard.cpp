#ifndef _APEX_BLACKBOARD
#define _APEX_BLACKBOARD
#include <apex_blackboard.hpp>
#include <arinc_module.hpp>
#include <circle/logger.h>
#include <partitionscheduling.hpp>

std::vector<PartitionBlackboard*> ApexBlackboard::partitionBlackboards{};
std::vector<PartitionStatus*> ApexBlackboard::partitionStatuses{};

bool ApexBlackboard::initialised = false;
/**
 * @brief Initialise the blackboards and statuses, based on partitions
 * This must be done, in order for the apex blackboards to function
 */
void ApexBlackboard::initPartitionBlackboards()
{
    // Get generated arinc module
    auto& module = ArincModule::generatedArincModule;

    // Create a blackboard and a status for each partition
    for (auto& partition : module.partitions) {
        partitionBlackboards.push_back(
            new PartitionBlackboard{*partition.getPartitionName().x.x, {}});
        partitionStatuses.push_back(
            new PartitionStatus{*partition.getPartitionName().x.x, {}});
    }

    // Set initialised
    initialised = true;
}

/**
 * @brief Create an APEX blackboard
 *
 * @param BLACKBOARD_NAME
 * @param MAX_MESSAGE_SIZE
 * @param BLACKBOARD_ID
 * @param RETURN_CODE
 */
void ApexBlackboard::CREATE_BLACKBOARD(
    /*in */ BLACKBOARD_NAME_TYPE BLACKBOARD_NAME,
    /*in */ MESSAGE_SIZE_TYPE MAX_MESSAGE_SIZE,
    /*out*/ BLACKBOARD_ID_TYPE* BLACKBOARD_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    assert(initialised && "ApexBlackboard must be initialised before use");

    // Create new blackboard in right partition
    auto* currentPartition = CyclicExecutiveSchedule::getCurrentPartition();
    int id = -1;
    for (auto& blackboard : partitionBlackboards) {
        if (blackboard->partitionName == *currentPartition->partitionName.x) {
            // Check if there is a blackboard with this name already
            if (blackboard->blackboards.size() > 0 &&
                *blackboard->blackboards[0]->blackboardName.x ==
                    *BLACKBOARD_NAME.x) {
                // Return NO_ACTION
                *RETURN_CODE = NO_ACTION;
                return;
            }

            // Insert the blackboard and status
            blackboard->blackboards.push_back(new Blackboard{BLACKBOARD_NAME, {}});

            for (auto& status : partitionStatuses) {
                if (status->partitionName == *currentPartition->partitionName.x) {
                    status->statuses.push_back(
                        new BLACKBOARD_STATUS_TYPE{EMPTY, MAX_MESSAGE_SIZE, 0});
                }
            }

            id = blackboard->blackboards.size() - 1;

            break;
        }
    }

    // Set return attributes
    assert(id != -1 && "Invalid partition name");
    *RETURN_CODE = NO_ERROR;
    *BLACKBOARD_ID = id;
}

void ApexBlackboard::DISPLAY_BLACKBOARD(
    /*in */ BLACKBOARD_ID_TYPE BLACKBOARD_ID,
    /*in */ MESSAGE_ADDR_TYPE* MESSAGE_ADDR, /* by reference */
    /*in */ MESSAGE_SIZE_TYPE LENGTH,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    auto* currentPartition = CyclicExecutiveSchedule::getCurrentPartition();
    bool exist = false;

    // Update status
    for (auto& status : partitionStatuses) {
        // Check for the current blackboard for this partition
        if (*currentPartition->partitionName.x == status->partitionName) {
            // Check if message is too big
            if (status->statuses.at(BLACKBOARD_ID)->MAX_MESSAGE_SIZE < LENGTH) {
                *RETURN_CODE = INVALID_PARAM;
                return;
            }

            status->statuses.at(BLACKBOARD_ID)->EMPTY_INDICATOR = OCCUPIED;
        }
    }

    // Update Blackboard
    for (auto& blackboard : partitionBlackboards) {
        // Check for the current blackboard for this partition
        if (*currentPartition->partitionName.x == blackboard->partitionName) {
            blackboard->blackboards.at(BLACKBOARD_ID)->message = MESSAGE_ADDR;
            exist = true;
        }
    }

    if (!exist) {
        *RETURN_CODE = NOT_AVAILABLE;
        return;
    }

    *RETURN_CODE = NO_ERROR;
}

void ApexBlackboard::READ_BLACKBOARD(
    /*in */ BLACKBOARD_ID_TYPE BLACKBOARD_ID,
    /*in */ SYSTEM_TIME_TYPE TIME_OUT,
    /*out*/ MESSAGE_ADDR_TYPE* MESSAGE_ADDR,
    /*out*/ MESSAGE_SIZE_TYPE* LENGTH,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    auto currentPartition = CyclicExecutiveSchedule::getCurrentPartition();

    bool exist = false;

    // Find the partition
    for (auto& blackboard : partitionBlackboards) {
        if (blackboard->partitionName == *currentPartition->partitionName.x) {
            MESSAGE_ADDR = blackboard->blackboards[BLACKBOARD_ID]->message;
            exist = true;
        }
    }

    // Check if the blackboard exist
    if (!exist) {
        *RETURN_CODE = NOT_AVAILABLE;
        return;
    }

    // Find the status
    for (auto& status : partitionStatuses) {
        if (status->partitionName == *currentPartition->partitionName.x) {
            *LENGTH = status->statuses.at(BLACKBOARD_ID)->MAX_MESSAGE_SIZE;
        }
    }

    *RETURN_CODE = NO_ERROR;
}

/**
 * @brief Get blackboard id by name
 *
 * @param BLACKBOARD_NAME
 * @param BLACKBOARD_ID
 * @param RETURN_CODE
 */
void ApexBlackboard::GET_BLACKBOARD_ID(
    /*in */ BLACKBOARD_NAME_TYPE BLACKBOARD_NAME,
    /*out*/ BLACKBOARD_ID_TYPE* BLACKBOARD_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    // Find partition blackboard
    for (auto& blackboard : partitionBlackboards) {
        // Find blackboard we are looking for and return
        if (blackboard->partitionName ==
            *CyclicExecutiveSchedule::getCurrentPartition()->partitionName.x) {
            if (blackboard->blackboards.size() == 0) {
                *RETURN_CODE = NOT_AVAILABLE;
                return;
            }
            int id = 0;
            for (auto& blackb : blackboard->blackboards) {
                if (*blackb->blackboardName.x == *BLACKBOARD_NAME.x) {
                    *BLACKBOARD_ID = id;
                    *RETURN_CODE = NO_ERROR;
                    return;
                }

                id++;
            }
        }
    }

    // If no blackboard were found
    *RETURN_CODE = INVALID_PARAM;
}

/**
 * @brief Get the status of any blackboard by id
 *
 * @param BLACKBOARD_ID
 * @param BLACKBOARD_STATUS
 * @param RETURN_CODE
 */
void ApexBlackboard::GET_BLACKBOARD_STATUS(
    /*in */ BLACKBOARD_ID_TYPE BLACKBOARD_ID,
    /*out*/ BLACKBOARD_STATUS_TYPE* BLACKBOARD_STATUS,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    for (auto& status : partitionStatuses) {
        if (status->partitionName ==
            *CyclicExecutiveSchedule::getCurrentPartition()->partitionName.x) {
            if (status->statuses.size() == 0) {
                *RETURN_CODE = NO_ACTION;
                return;
            }
            else if (status->statuses.size() < BLACKBOARD_ID) {
                *RETURN_CODE = INVALID_PARAM;
                return;
            }

            BLACKBOARD_STATUS = status->statuses[BLACKBOARD_ID];
            *RETURN_CODE = NO_ERROR;
            return;
        }
    }

    *RETURN_CODE = INVALID_PARAM;
}

#endif