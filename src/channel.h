#include "general_types.h"

class Channel {
	private:
		IdentifierValueType channelIdentifier;					/* required */
		std::optional<NameType> channelName;						/* optional */
    PortMappingType source;													/* required */
		PortMappingType destination[PARTITION_NUMBER];	/* required */
}
