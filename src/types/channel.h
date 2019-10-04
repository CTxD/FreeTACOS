#include "general_types.h"

#ifndef CHANNEL
#define CHANNEL

class Channel
{
	private:
		identifierValueType channelIdentifier;			/* required */
		std::optional<nameType> channelName;			/* optional */
		PortMappingType source;							/* required */
		PortMappingType destination[PARTITION_NUMBER];	/* required */
};

#endif
