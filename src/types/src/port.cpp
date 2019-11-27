#include "include/port.hpp"

const name_t& Port::getPortName() const
{
  return portName;
}

const APEX_INTEGER& Port::getMaxMessageSize() const
{
  return maxMessageSize;
}

const PORT_DIRECTION_TYPE& Port::getDirection() const
{
  return direction;
}
