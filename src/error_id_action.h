#include "general_types.h"

#ifndef ERROR_ID_ACTION
#define ERROR_ID_ACTION

typedef
    enum ModuleActionType
    {
        IGNORE      = 0;
        SHUTDOWN    = 1;
        RESET       = 2;
    };

class ErrorIDAction
{
    private:
        int ErrorIdentifier;                    /* required */
        std::optional<NameType> Description;   /* optional */
        ModuleActionType Action;                /* required */
};

#endif
