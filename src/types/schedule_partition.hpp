#ifndef __SCHEDULE_PARTITION__
#define __SCHEDULE_PARTITION__

#include "general_types.h"

class SchedulePartition {
private:
    name_t nameRef;
    int affinity;
    int duration;
    int period;
    int offset;

public:
    SchedulePartition(name_t nameRef, int affinity, int duration, int period, int offset)
        : nameRef(nameRef), affinity(affinity), duration(duration), period(period), offset(offset)
    {
    }
};

#endif
