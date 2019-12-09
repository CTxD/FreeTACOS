#ifndef CHANNEL
#define CHANNEL

#include "port_mapping.hpp"

class Channel {
private:
    PortMapping portMapping[100];
    MemoryArea portMappingArea{std::data(portMapping), std::size(portMapping)};
    MonotonicMemoryResource<> portBufferSrc{portMappingArea};
    MonotonicAllocator<PortMapping> portMappingAllocator{portBufferSrc};

    identifier_t channelIdentifier;       /* required */
    std::optional<NAME_TYPE> channelName; /* optional */
    PortMapping source;                   /* required */
    std::vector<PortMapping, MonotonicAllocator<PortMapping>> destinations{
        portMappingAllocator}; /* required */

public:
    Channel(){};

    Channel(identifier_t id, NAME_TYPE name, PortMapping source, std::initializer_list<PortMapping> destinations)
        : channelIdentifier(id), channelName(name), source(source), destinations(destinations)
    {
    }

    const identifier_t& getChannelId() const;

    const std::optional<NAME_TYPE>& getChannelName() const;

    const PortMapping& getSource() const;

    const std::vector<PortMapping, MonotonicAllocator<PortMapping>>& getDestinations() const;
};

#endif
