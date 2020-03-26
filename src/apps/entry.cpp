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
        10,   10,         new TestApp(logger, {"flightManagement"}), 0x8000, 10,
        HARD, {"TestApp"}};

    PROCESS_ATTRIBUTE_TYPE systemManagementProcess = PROCESS_ATTRIBUTE_TYPE{
        10,   10,         new TestApp(logger, {"systemManagement"}), 0x8000, 10,
        HARD, {"TestApp"}};

    PROCESS_ATTRIBUTE_TYPE flightControlsProcess = PROCESS_ATTRIBUTE_TYPE{
        10,   10,         new TestApp(logger, {"flightControls"}), 0x8000, 10,
        HARD, {"TestApp"}};

    // Create the process
    PROCESS_ID_TYPE returnId1, returnId2, returnId3;
    RETURN_CODE_TYPE returnCode1, returnCode2, returnCode3;
    CREATE_PROCESS(&flightManagementProcess, &returnId1, &returnCode1);
    CREATE_PROCESS(&systemManagementProcess, &returnId2, &returnCode2);
    CREATE_PROCESS(&flightControlsProcess, &returnId3, &returnCode3);

    if (returnCode1 == RETURN_CODE_TYPE::NO_ERROR && returnCode2 == RETURN_CODE_TYPE::NO_ERROR &&
        returnCode3 == RETURN_CODE_TYPE::NO_ERROR) {
        logger->Write(*getProcessName().x, LogNotice,
                      "All Processes was successfully created");
    }
    else {
        logger->Write(*getProcessName().x, LogNotice,
                      "Error %s occured, while creating processes");
    }
}