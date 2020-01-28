#include "consumer_part.h"
#include "circle/logger.h"

ConsumerPart::ConsumerPart(CLogger* logger, QueuingPort* q)
    : mLogger(logger), receivePort(q)
{
}

void ConsumerPart::Run()
{
    mLogger->Write(nameRef, LogNotice, "Consumes Fib(10) times...");
    for (int i = 0; i < 10; i++) {
        mLogger->Write(nameRef, LogNotice, "Consuming fib number - %s",
                       receivePort->getMessage());
    }
}
