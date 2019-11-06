#include <arch.h>

class CTacosKernel : public CBootableKernel
{
private:
public:
    CTacosKernel();
    CStdlibApp::TShutdownMode Run();
    ~CTacosKernel();
};