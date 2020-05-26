#include <apex_buffer.hpp>
#include <apex_kernel.hpp>
#include <entry.hpp>
#include <lyngsoe/blr_lll_host_service.hpp>
#include <lyngsoe/data_processor_service.hpp>
#include <lyngsoe/io_blr_service.hpp>
#include <lyngsoe/rfid_reader.hpp>
#include <test_app.hpp>

#include <vector>

Entry::Entry(CLogger* logger)
    : Task(10, 10, 10, HARD, {"EntryApp"}, {"systemManagement"})
{
    this->logger = logger;
}

Entry::~Entry()
{
}

void Entry::Run(void)
{
    // Create a buffer
    BUFFER_ID_TYPE id;
    RETURN_CODE_TYPE code;
    ApexBuffer::CREATE_BUFFER({"IOBuffer"}, 30, 0, FIFO, &id, &code);

    // Define processes
    std::vector<PROCESS_ATTRIBUTE_TYPE> processes = {
        PROCESS_ATTRIBUTE_TYPE{
            2000 * HZ, 10, new BlrLllHostServiceTask(), 0x8000, 10, HARD, {"BlrLllHostService"}},
        PROCESS_ATTRIBUTE_TYPE{
            2000 * HZ, 10, new DataProcessorServiceTask(), 0x8000, 10, HARD, {"DataProcessorService"}},
        PROCESS_ATTRIBUTE_TYPE{
            2000 * HZ, 10, new Io2BlrServiceTask(), 0x8000, 10, HARD, {"Io2BlrService"}},
        PROCESS_ATTRIBUTE_TYPE{
            2000 * HZ, 10, new RfidReaderTask(), 0x8000, 10, HARD, {"RfidReaderService"}},
    };

    // Create processes
    for (auto proc : processes) {
        PROCESS_ID_TYPE id;
        RETURN_CODE_TYPE code;

        CREATE_PROCESS(&proc, &id, &code);

        if (code == NO_ERROR) {
            logger->Write({"Kernel"}, LogNotice, "%s created with id %d",
                          *proc.NAME.x, id);
        }
        else {
            logger->Write({"Kernel"}, LogNotice, "Error creating %s", *proc.NAME.x);
            break;
        }
    }
}