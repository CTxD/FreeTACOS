#include <apex_event.hpp>

std::vector<CEvent*> ApexEvent::events = {};

/**
 * @brief Create an event
 *
 * @param EVENT_NAME
 * @param EVENT_ID
 * @param RETURN_CODE
 */
void ApexEvent::CREATE_EVENT(
    /*in */ EVENT_NAME_TYPE EVENT_NAME,
    /*out*/ EVENT_ID_TYPE* EVENT_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    auto* event = new CEvent{
        EVENT_NAME, {EVENT_STATE_TYPE::DOWN, 0}, new CSynchronizationEvent()};
    events.push_back(event);

    *EVENT_ID = events.size() - 1;
    *RETURN_CODE = NO_ERROR;
}

/**
 * @brief Set an event, changing it's status to UP
 *
 * @param EVENT_ID
 * @param RETURN_CODE
 */
void ApexEvent::SET_EVENT(
    /*in */ EVENT_ID_TYPE EVENT_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    // Check if the event exist
    if (events.size() - 1 < EVENT_ID) {
        *RETURN_CODE = INVALID_PARAM;
        return;
    }

    // Set the event
    events.at(EVENT_ID)->CircleEvent->Set();

    // Update status
    events.at(EVENT_ID)->status.EVENT_STATE = EVENT_STATE_TYPE::UP;

    *RETURN_CODE = NO_ERROR;
}

/**
 * @brief Reset an event, changing it's status to DOWN
 *
 * @param EVENT_ID
 * @param RETURN_CODE
 */
void ApexEvent::RESET_EVENT(
    /*in */ EVENT_ID_TYPE EVENT_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    // Check if the event exist
    if (events.size() - 1 < EVENT_ID) {
        *RETURN_CODE = INVALID_PARAM;
        return;
    }

    // Reset the event
    events.at(EVENT_ID)->CircleEvent->Clear();

    // Update status
    events.at(EVENT_ID)->status.EVENT_STATE = EVENT_STATE_TYPE::DOWN;
    events.at(EVENT_ID)->status.WAITING_PROCESSES = 0;

    *RETURN_CODE = NO_ERROR;
}

/**
 * @brief Wait for an event to trigger
 *
 * @param EVENT_ID
 * @param TIME_OUT
 * @param RETURN_CODE
 */
void ApexEvent::WAIT_EVENT(
    /*in */ EVENT_ID_TYPE EVENT_ID,
    /*in */ SYSTEM_TIME_TYPE TIME_OUT,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    // Check if the event exist
    if (events.size() - 1 < EVENT_ID) {
        *RETURN_CODE = INVALID_PARAM;
        return;
    }

    // Wait the event
    // TODO: Implement the timeout
    events.at(EVENT_ID)->CircleEvent->Wait();

    // Update status
    events.at(EVENT_ID)->status.WAITING_PROCESSES++;

    *RETURN_CODE = NO_ERROR;
}

/**
 * @brief Get the id of an event by name
 *
 * @param EVENT_NAME
 * @param EVENT_ID
 * @param RETURN_CODE
 */
void ApexEvent::GET_EVENT_ID(
    /*in */ EVENT_NAME_TYPE EVENT_NAME,
    /*out*/ EVENT_ID_TYPE* EVENT_ID,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    // Find the event
    int id = 0;
    for (auto& event : events) {
        // Match on events
        if (*EVENT_NAME.x == *event->eventName.x) {
            *EVENT_ID = id;
            *RETURN_CODE = NO_ERROR;
            return;
        }
        id++;
    }

    // Nothing found
    *RETURN_CODE = INVALID_PARAM;
    return;
}

/**
 * @brief Get the status of an event by id
 *
 * @param EVENT_ID
 * @param EVENT_STATUS
 * @param RETURN_CODE
 */
void ApexEvent::GET_EVENT_STATUS(
    /*in */ EVENT_ID_TYPE EVENT_ID,
    /*out*/ EVENT_STATUS_TYPE* EVENT_STATUS,
    /*out*/ RETURN_CODE_TYPE* RETURN_CODE)
{
    // Check if the event exist
    if (events.size() - 1 < EVENT_ID) {
        *RETURN_CODE = INVALID_PARAM;
        return;
    }

    // Return the event
    *EVENT_STATUS = events.at(EVENT_ID)->status;
    *RETURN_CODE = NO_ERROR;
}
