#include <apex_blackboard.hpp>
#include <circle/logger.h>

std::vector<BLACKBOARD_STATUS_TYPE> ApexBlackboard::blackboardStatuses[MAX_NUMBER_OF_BLACKBOARDS]{};
std::map<char*, void*> ApexBlackboard::blackboards[MAX_NUMBER_OF_BLACKBOARDS]{}; // Void* to take any message

void ApexBlackboard::CREATE_BLACKBOARD(
    /*in */ BLACKBOARD_NAME_TYPE BLACKBOARD_NAME,
    /*in */ MESSAGE_SIZE_TYPE MAX_MESSAGE_SIZE,
    /*out*/ BLACKBOARD_ID_TYPE* BLACKBOARD_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    // Check if we have exceeded the number of blackboards
    if (blackboards->size() > MAX_NUMBER_OF_BLACKBOARDS) {
        *RETURN_CODE = RETURN_CODE_TYPE::INVALID_CONFIG;
    }

    auto id = blackboards->size();

    // Create an empty blackboard
    (*blackboards)[(char*)BLACKBOARD_NAME.x] = nullptr;

    // Create new status for this blackboard
    blackboardStatuses->push_back({EMPTY_INDICATOR_TYPE::EMPTY, MAX_MESSAGE_SIZE, {}});

    // Set return attributes
    *RETURN_CODE = NO_ERROR;
    *BLACKBOARD_ID = id;
}