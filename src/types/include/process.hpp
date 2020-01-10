#ifndef PROCESS_H
#define PROCESS_H

#include "apex_process.h"
#include "general_types.hpp"

#ifdef HOST_TESTING
#include <catch2/taskRegisters.hpp>
#else
#include <circle/sched/taskswitch.h>
#endif

class Process {
private:
    identifier_t id;
    PROCESS_STATUS_TYPE status;
    TTaskRegisters registers;

public:
    Process()
    {
    }

    Process(identifier_t id, PROCESS_STATUS_TYPE status, TTaskRegisters regs)
        : id(id), status(status), registers(regs)
    {
    }

    Process(const Process& rhs)
        : id(rhs.id), status(rhs.status), registers(rhs.registers)
    {
    }

    const PROCESS_STATUS_TYPE& getStatus() const;

    const PROCESS_ATTRIBUTE_TYPE& getAttributes() const;

    const identifier_t& getId() const;

    RETURN_CODE_TYPE setRegs(TTaskRegisters registers) const;

    const TTaskRegisters& getRegs();
};

#endif
