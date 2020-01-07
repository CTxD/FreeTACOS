#ifndef TACOS_PROCESS_INTERFACE
#define TACOS_PROCESS_INTERFACE
class IProcess {
protected:
    const char* nameRef;

public:
    IProcess(const char* name) : nameRef(name){};
    virtual ~IProcess(){};
    virtual void run() = 0;
    virtual bool initialise() = 0;
};
#endif