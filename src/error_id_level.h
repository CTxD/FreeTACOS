#include <general_types.h>

typedef 
    enum ErrorLevelType
    {
        MODULE      = 0;
        PARTITION   = 1;
        PROCESS     = 2;
    }

typedef 
    enum ErrorCodeType
    {
        DEADLINE_MISSED     = 0;
        APPLICATION_ERROR   = 1;
        NUMERIC_ERROR       = 2;
        ILLEGAL_REQUEST     = 3;
        STACK_OVERFLOW      = 4;
        MEMORY_VIOLATION    = 5;
        HARDWARE_FAULT      = 6;
        POWER_FAILURE       = 7;
    }

class ErrorIDLevel
{
    private:
        int error_identifier;                       /* required */
        std::optional<NameType> description;       /* optional */
        ErrorLevelType error_level;                 /* required */
        std::optional<ErrorCodeType> error_code;   /* optional */
}