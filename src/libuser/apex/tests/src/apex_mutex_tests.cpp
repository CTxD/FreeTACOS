#include <apex_mutex_tests.hpp>
#include <apex_mutex.hpp>
#include <partitionscheduling.hpp>
#include <arch.h>

void TestCreateMutexOutput(){
    CLogger::Get()->Write("APEX TEST", LogNotice, "Testing create mutex output");
    MUTEX_ID_TYPE id;
    RETURN_CODE_TYPE code;
    
    ApexMutex::InitializeMutex();

    CyclicExecutiveSchedule::GetCurrentPartition()->operatingMode = {
        OPERATING_MODE_TYPE::COLD_START};

    CyclicExecutiveSchedule::GetCurrentPartition()->partitionName = {
        "asdasdasd"};
    
    ApexMutex::CREATE_MUTEX({"TestMutex"}, 1, QUEUING_DISCIPLINE_TYPE::FIFO, &id, &code);
    assert(code == NOT_AVAILABLE);
    CLogger::Get()->Write("APEX TEST", LogNotice, 
                            "Creating mutex with non existing partition. return code NOT_AVAILABLE : PASSED");
    
    CyclicExecutiveSchedule::GetCurrentPartition()->partitionName = {
        "IOProcessing"};
    
    ApexMutex::CREATE_MUTEX({"TestMutex"}, 1, QUEUING_DISCIPLINE_TYPE::FIFO, &id, &code);
    assert(code == NO_ERROR);
    CLogger::Get()->Write("APEX TEST", LogNotice, "Created mutex. return code NO_ERROR : PASSED");

    ApexMutex::CREATE_MUTEX({"TestMutex"}, 4, QUEUING_DISCIPLINE_TYPE::FIFO, &id, &code);
    assert(code == INVALID_PARAM);
    CLogger::Get()->Write("APEX TEST", LogNotice,
                            "Created mutex with exidind priority. return code INVALID_PARAM : PASSED");
    
    ApexMutex::CREATE_MUTEX({"TestMutex"}, 1, QUEUING_DISCIPLINE_TYPE::FIFO, &id, &code);
    assert(code == NO_ACTION);
    CLogger::Get()->Write("APEX TEST", LogNotice, "Created existing mutex. return code NO_ACTION : PASSED");
}