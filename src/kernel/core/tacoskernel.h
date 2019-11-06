#include <arch.h>

class CTacosKernel : public CKernel {
private:
public:
    CTacosKernel();
    CStdlibApp::TShutdownMode Run();
    ~CTacosKernel();
};