#ifndef PROCESS_H
#define PROCESS_H

#include "apex_process.h"
#include "general_types.hpp"

class Process {
private:
    identifier_t id;
    PROCESS_STATUS_TYPE status;

public:
    Process()
    {
    }

    Process(identifier_t id, PROCESS_STATUS_TYPE status)
        : id(id), status(status)
    {
    }

    Process(const Process& rhs) : id(rhs.id), status(rhs.status)
    {
    }

    const PROCESS_STATUS_TYPE& getStatus() const;

    const PROCESS_ATTRIBUTE_TYPE& getAttributes() const;

    const identifier_t& getId() const;
};

#endif
