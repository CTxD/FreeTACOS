#ifndef __FREETACOS_ARCH__
#define __FREETACOS_ARCH__

#include <circle_stdlib_app.h>
#include <errcode.h>

class CKernel : public CStdlibAppStdio {
public:
    CKernel(void);

    TShutdownMode Run(void);
};

#endif