#ifndef ERROR_ID_LEVEL
#define ERROR_ID_LEVEL

#include "general_types.h"

enum ErrorLevelType
{
    MODULE      = 0,
    PARTITION   = 1,
    PROCESS     = 2,
};

enum ErrorCodeType
{
    DEADLINE_MISSED     = 0,
    APPLICATION_ERROR   = 1,
    NUMERIC_ERROR       = 2,
    ILLEGAL_REQUEST     = 3,
    STACK_OVERFLOW      = 4,
    MEMORY_VIOLATION    = 5,
    HARDWARE_FAULT      = 6,
    POWER_FAILURE       = 7,
};

class ErrorIDLevel
{
    private:
        int errorIdentifier;                       /* required */
        std::optional<NameType> description;        /* optional */
        ErrorLevelType error_level;                 /* required */
        std::optional<ErrorCodeType> error_code;    /* optional */

    public:
        ErrorIDLevel(int id, NameType description, ErrorLevelType level, ErrorCodeType code):
          errorIdentifier(id), description(description), error_level(level), error_code(code) {}
};

#endif
