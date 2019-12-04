#ifndef PORT_TYPE
#define PORT_TYPE

#include "apex_types.h"
#include "port_mapping.hpp"


class Port
{
  private:
    NAME_TYPE portName;                /* required */
    APEX_INTEGER maxMessageSize;    /* required */
    PORT_DIRECTION_TYPE direction;  /* required */

  public:
    Port() {}

    Port(NAME_TYPE name,APEX_INTEGER msgSize, PORT_DIRECTION_TYPE dir):
      portName(name), maxMessageSize(msgSize), direction(dir) {}

    const NAME_TYPE& getPortName() const;

    const APEX_INTEGER& getMaxMessageSize() const;

    const PORT_DIRECTION_TYPE& getDirection() const;
};

#endif
