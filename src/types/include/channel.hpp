#ifndef CHANNEL
#define CHANNEL

#include "port_mapping.hpp"

class Channel {
private:
    PortMapping destination[1];
    std::vector<PortMapping>* destinations = new (&destination) std::vector<PortMapping>;

    identifier_t channelIdentifier;       /* required */
    std::optional<NAME_TYPE> channelName; /* optional */
    PortMapping source;                   /* required */

public:
    Channel(){};

    Channel(identifier_t id, NAME_TYPE name, PortMapping source, std::initializer_list<PortMapping> dest)
        : channelIdentifier(id), channelName(name), source(source)
    {
        for (auto d : dest) {
            destinations->push_back(d);
        }
    }

    const identifier_t& getChannelId() const;

    const std::optional<NAME_TYPE>& getChannelName() const;

    const PortMapping& getSource() const;

    const std::vector<PortMapping>& getDestinations() const;
};

#endif
