#ifndef PROCESS_H
#define PROCESS_H

#include "apex_process.h"
#include "apex_types.h"
#include "general_types.hpp"

class Process {
private:
    PROCESS_STATUS_TYPE processStatus;
    PROCESS_ATTRIBUTE_TYPE processAttributes;

public:
    Process(PROCESS_ATTRIBUTE_TYPE& attributes);
    Process(PROCESS_STATUS_TYPE& status);

    const PROCESS_STATUS_TYPE& getStatus() const;
    const PROCESS_ATTRIBUTE_TYPE& getAttributes() const;
    const PROCESS_NAME_TYPE& getProcessIdentifier() const;

    PROCESS_STATE_TYPE& getProcessState();
    void setProcessState(PROCESS_STATE_TYPE& state);

    name_t getProcessName();

    void CREATE_PROCESS(
        /*in */ PROCESS_ATTRIBUTE_TYPE* ATTRIBUTES,
        /*out*/ PROCESS_ID_TYPE* PROCESS_ID,
        /*out*/ RETURN_CODE_TYPE* RETURN_CODE);
};

#endif