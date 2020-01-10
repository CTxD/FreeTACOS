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

void Process::setRegs(TTaskRegisters regs)
{
	registers = regs;
}

const TTaskRegisters& Process::getRegs() const
{
	return registers;
}