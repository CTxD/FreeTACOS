#ifndef SAMPLING_PORT
#define SAMPLING_PORT

#include "port.h"

class SamplingPort : Port
{
    private:
        std::optional<float> refreshRate;  /* optional */

    public:
        SamplingPort(name_t name,APEX_INTEGER msgSize, PORT_DIRECTION_TYPE direction, float refreshRate):
          Port(name, msgSize, direction), refreshRate(refreshRate) {}

        float getRefreshRate();
};

#endif
