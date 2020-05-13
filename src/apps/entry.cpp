/**
 * Entry App.
 * This class is meant to be the entry point for process execution,
 * therefore, this process should create all other processes, for their
 * respective partitions
 */

#include <entry.hpp>
#include <lyngsoe/blr_lll_host_service.hpp>
#include <lyngsoe/data_processor_service.hpp>
#include <lyngsoe/diagnosis_service.hpp>
#include <lyngsoe/gps_service.hpp>
#include <lyngsoe/io_blr_service.hpp>
#include <lyngsoe/io_service.hpp>
#include <lyngsoe/output_service.hpp>
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
    // Define processes
    std::vector<PROCESS_ATTRIBUTE_TYPE> processes = {
        PROCESS_ATTRIBUTE_TYPE{
            2000 * HZ, 10, new BlrLllHostServiceTask(), 0x8000, 10, HARD, {"BlrLllHostService"}},
        PROCESS_ATTRIBUTE_TYPE{
            2000 * HZ, 10, new DataProcessorServiceTask(), 0x8000, 10, HARD, {"DataProcessorService"}},
        PROCESS_ATTRIBUTE_TYPE{
            2000 * HZ, 10, new DiagnosisServiceTask(), 0x8000, 10, HARD, {"DiagnosisService"}},
        PROCESS_ATTRIBUTE_TYPE{
            2000 * HZ, 10, new GpsServiceTask(), 0x8000, 10, HARD, {"GpsService"}},
        PROCESS_ATTRIBUTE_TYPE{
            2000 * HZ, 10, new Io2BlrServiceTask(), 0x8000, 10, HARD, {"Io2BlrService"}},
        PROCESS_ATTRIBUTE_TYPE{
            2000 * HZ, 10, new IoServiceTask(), 0x8000, 10, HARD, {"IoService"}},
        PROCESS_ATTRIBUTE_TYPE{
            2000 * HZ, 10, new OutputServiceTask(), 0x8000, 10, HARD, {"OutputService"}},
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

    /*
    logger->Write(*getProcessName().x, LogNotice, "Entry App instantiated");
    logger->Write(*getProcessName().x, LogNotice, "Creating processes...");

    // Define process attributes
    PROCESS_ATTRIBUTE_TYPE flightManagementProcess = PROCESS_ATTRIBUTE_TYPE{
        1000 * HZ,   10, new TestApp(logger, {"flightManagement"}),
        0x8000,      10, HARD,
        {"TestApp1"}};

    PROCESS_ATTRIBUTE_TYPE systemManagementProcess = PROCESS_ATTRIBUTE_TYPE{
        2000 * HZ,   10, new TestApp(logger, {"systemManagement"}),
        0x8000,      10, HARD,
        {"TestApp2"}};

    PROCESS_ATTRIBUTE_TYPE flightControlsProcess = PROCESS_ATTRIBUTE_TYPE{
        3000 * HZ, 10, new TestApp(logger, {"flightControls"}),
        0x8000,    10, HARD,
        {"FC APP"}};

    PROCESS_ATTRIBUTE_TYPE IHVMProcess = PROCESS_ATTRIBUTE_TYPE{
        4000 * HZ, 10,          new TestApp(logger, {"IHVM "}), 0x8000, 10,
        HARD,      {"IHVM APP"}};

    PROCESS_ATTRIBUTE_TYPE IOProcessingProcess11 = PROCESS_ATTRIBUTE_TYPE{
        10000 * HZ, 3, new TestApp(logger, {"IOProcessing"}), 0x8000, 10, HARD, {"Slow Responsive App"}};

    PROCESS_ATTRIBUTE_TYPE IOProcessingProcess12 = PROCESS_ATTRIBUTE_TYPE{
        3000 * HZ, 2, new TestApp(logger, {"IOProcessing"}), 0x8000, 10, HARD, {"Fast Responsive App"}};

    PROCESS_ATTRIBUTE_TYPE IOProcessingProcess13 = PROCESS_ATTRIBUTE_TYPE{
        6000 * HZ, 2, new TestApp(logger, {"IOProcessing"}), 0x8000, 10, HARD, {"Medium Responsive App"}};

    // Create the process
    PROCESS_ID_TYPE returnId1, returnId2, returnId3, returnId4, returnId31,
        returnId32, returnId33;
    RETURN_CODE_TYPE returnCode1, returnCode2, returnCode3, returnCode4,
        returnCode31, returnCode32, returnCode33;
    CREATE_PROCESS(&flightManagementProcess, &returnId1, &returnCode1);
    CREATE_PROCESS(&systemManagementProcess, &returnId2, &returnCode2);
    CREATE_PROCESS(&flightControlsProcess, &returnId3, &returnCode3);
    CREATE_PROCESS(&IHVMProcess, &returnId4, &returnCode4);
    CREATE_PROCESS(&IOProcessingProcess11, &returnId31, &returnCode31);
    CREATE_PROCESS(&IOProcessingProcess12, &returnId32, &returnCode32);
    CREATE_PROCESS(&IOProcessingProcess13, &returnId33, &returnCode33);

    if (returnCode1 == RETURN_CODE_TYPE::NO_ERROR && returnCode2 == RETURN_CODE_TYPE::NO_ERROR &&
        returnCode31 == RETURN_CODE_TYPE::NO_ERROR &&
        returnCode32 == RETURN_CODE_TYPE::NO_ERROR &&
        returnCode33 == RETURN_CODE_TYPE::NO_ERROR) {
        logger->Write(*getProcessName().x, LogNotice,
                      "All Processes was successfully created");
    }
    else {
        logger->Write(*getProcessName().x, LogNotice,
                      "Error %s occured, while creating processes");
    }
    */
}