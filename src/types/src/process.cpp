#include "include/process.hpp"

const PROCESS_STATUS_TYPE& Process::getStatus() const
{
    return status;
}

const PROCESS_ATTRIBUTE_TYPE& Process::getAttributes() const
{
    return status.ATTRIBUTES;
}

const identifier_t& Process::getId() const
{
    return id;
}

RETURN_CODE_TYPE setRegs(TTaskRegisters regs) const
{
	registers = regs;
}

const TTaskRegisters& getRegs()
{
	return registers;
}