#ifndef PROCESS_H
#define PROCESS_H

#include "general_types.h"


class Process
{
    private:
        name_t name;                          /* required */
        std::optional<decOrHex_t> stackSize;  /* optional */

    public:
        Process() {};
        Process(name_t& name, decOrHex_t size):
          name(std::move(name)), stackSize(size) {}
};

#endif
