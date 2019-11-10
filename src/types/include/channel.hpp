#ifndef CHANNEL
#define CHANNEL

#include "port_mapping.hpp"


class Channel
{
	private:
		PortMapping portMapping[100];
    	monotonic_buffer_resource portMappingSrc{std::data(portMapping),
                                               std::size(portMapping)};
		identifier_t channelIdentifier;			/* required */
		std::optional<name_t> channelName;	/* optional */
		PortMapping source;									/* required */
		vector<PortMapping> destinations; 	/* required */

	public:
		Channel() {};

		Channel(identifier_t id, name_t name, PortMapping source, std::initializer_list<PortMapping> destinations):
			channelIdentifier(id), channelName(name), source(source), destinations(destinations, &portMappingSrc) {}

		const identifier_t& getChannelId() const;

		const std::optional<name_t>& getChannelName() const;

		const PortMapping& getSource() const;

		const vector<PortMapping>& getDestinations() const;
};

#endif
