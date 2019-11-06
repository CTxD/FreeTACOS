#ifndef __FREETACOS_ARCH__
#define __FREETACOS_ARCH__

#include <circle/actled.h>
#include <circle/devicenameservice.h>
#include <circle/koptions.h>
#include <circle/logger.h>
#include <circle/memory.h>
#include <circle/screen.h>
#include <circle/serial.h>
#include <circle/types.h>
#include <circle_stdlib_app.h>
#include <errcode.h>

class CKernel : public CStdlibAppStdio {
public:
    CKernel(void);

    CLogger GetLogger()
    {
        return mLogger;
    };

    TShutdownMode Run(void);
};

#endif