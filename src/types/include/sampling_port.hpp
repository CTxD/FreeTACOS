#ifndef SAMPLING_PORT
#define SAMPLING_PORT

#include "port.hpp"

class SamplingPort : Port {
private:
    std::optional<float> refreshRate; /* optional */

public:
    SamplingPort()
    {
    }

    SamplingPort(name_t name, APEX_INTEGER msgSize, PORT_DIRECTION_TYPE direction, float refreshRate)
        : Port(name, msgSize, direction), refreshRate(refreshRate)
    {
    }

    const std::optional<float>& getRefreshRate() const;
};

#endif
