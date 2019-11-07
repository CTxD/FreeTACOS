#ifndef CHANNEL
#define CHANNEL

#include "port_mapping.h"


class Channel
{
	private:

		PortMappingType portMappingType[100];
    	monotonic_buffer_resource portMappingTypeSrc{std::data(portMappingType),
                                                    std::size(portMappingType)};
		identifier_t channelIdentifier;				/* required */
		std::optional<name_t> channelName;			/* optional */
		PortMappingType source;						/* required */
		vector<PortMappingType> destination; 		/* required */

	public:
		Channel() {};
		Channel(identifier_t id, name_t name, PortMappingType source, std::initializer_list<PortMappingType> destinations):
			channelIdentifier(id), channelName(name), source(source), destination(destinations, &portMappingTypeSrc) {}
};

#endif
