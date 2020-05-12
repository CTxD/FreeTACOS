/**
 * Entry App.
 * This class is meant to be the entry point for process execution,
 * therefore, this process should create all other processes, for their
 * respective partitions
 */

#include <entry.hpp>
#include <test_app.hpp>

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
    logger->Write(*getProcessName().x, LogNotice, "Entry App instantiated");
    logger->Write(*getProcessName().x, LogNotice, "Creating processes...");

    // Define process attributes
    PROCESS_ATTRIBUTE_TYPE flightManagementProcess = PROCESS_ATTRIBUTE_TYPE{
        150000 * HZ, 10, new TestApp(logger, {"flightManagement"}),
        0x8000,      10, HARD,
        {"TestApp1"}};

    PROCESS_ATTRIBUTE_TYPE systemManagementProcess = PROCESS_ATTRIBUTE_TYPE{
        150000 * HZ, 10, new TestApp(logger, {"systemManagement"}),
        0x8000,      10, HARD,
        {"TestApp2"}};

    PROCESS_ATTRIBUTE_TYPE flightControlsProcess = PROCESS_ATTRIBUTE_TYPE{
        150000 * HZ, 10, new TestApp(logger, {"flightControls"}),
        0x8000,      10, HARD,
        {"FC APP"}};

    PROCESS_ATTRIBUTE_TYPE IHVMProcess = PROCESS_ATTRIBUTE_TYPE{
        150000 * HZ, 10,          new TestApp(logger, {"IHVM "}), 0x8000, 10,
        HARD,        {"IHVM APP"}};

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
}