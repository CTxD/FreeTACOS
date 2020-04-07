#ifndef _FREETACOS_ENTRY_
#define _FREETACOS_ENTRY_

#include <task.hpp>

#include <circle/logger.h>

#include <apex_process.hpp>

class Entry : Task {
public:
    Entry(CLogger* logger);
    ~Entry(void);

    void Run(void);

private:
    CLogger* logger;
};

#endif