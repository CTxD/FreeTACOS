#include <apex_buffer_tests.hpp>
#include <apex_buffer.hpp>
#include <partitionscheduling.hpp>
#include <test_app.hpp>
#include <circle/logger.h>
#include <arch.h>


void CreateBufferFunctionalTest(){
    CLogger::Get()->Write("APEX TEST", LogNotice, "Testing create buffer output");
    CyclicExecutiveSchedule::GetCurrentPartition()->partitionName = {
        "IOProcessing"};
    
    BUFFER_ID_TYPE id;
    RETURN_CODE_TYPE code;

    ApexBuffer::initialiseBuffers();

    CyclicExecutiveSchedule::GetCurrentPartition()->partitionName = {
        "asdasdasd"};
        
    ApexBuffer::CREATE_BUFFER({"BUFFER_CREATE_TEST"}, 5, 100, FIFO, &id, &code);
    assert(code == NOT_AVAILABLE);
    CLogger::Get()->Write("APEX TEST", LogNotice, "Creating buffer with non existing partition. return code NOT_AVAILABLE : PASSED");

    CyclicExecutiveSchedule::GetCurrentPartition()->partitionName = {
        "IOProcessing"};

    ApexBuffer::CREATE_BUFFER({"BUFFER_CREATE_TEST"}, 5, 100, FIFO, &id, &code);
    assert(code == NO_ERROR);
    CLogger::Get()->Write("APEX TEST", LogNotice, "Created buffer. return code NO_ERROR : PASSED");

    ApexBuffer::CREATE_BUFFER({"BUFFER_CREATE_TEST"}, 5, 100, FIFO, &id, &code);
    assert(code == INVALID_PARAM);
    CLogger::Get()->Write("APEX TEST", LogNotice, "Created existing buffer. return code INVALID_PARAM : PASSED");

}

void SendBufferFunctionalTest(){
    CLogger::Get()->Write("APEX TEST", LogNotice, "Testing send buffer functional test");
    CyclicExecutiveSchedule::GetCurrentPartition()->partitionName = {
        "IOProcessing"};
    CyclicExecutiveSchedule::GetCurrentPartition()->operatingMode = {
        OPERATING_MODE_TYPE::NORMAL};
    

    CLogger* logger =  CLogger::Get();
    PROCESS_ATTRIBUTE_TYPE IOProcessingProcess11 = PROCESS_ATTRIBUTE_TYPE{
        10000 * HZ, 3, new TestApp(logger, {"IOProcessing"}), 0x8000, 10, HARD, {"P1"}};

    BUFFER_ID_TYPE id;
    RETURN_CODE_TYPE code;
    auto sendMessage = MESSAGE_ADDR_TYPE(APEX_BYTE('Test'));
    auto receiveMessage = MESSAGE_ADDR_TYPE(APEX_BYTE('Test'));
    MESSAGE_SIZE_TYPE messageSize = (APEX_BYTE)4;

    ProcessSchedule::InitialiseSchedules();
    ApexBuffer::initialiseBuffers();

    ApexBuffer::CREATE_BUFFER({"B1"}, 5, 100, FIFO, &id, &code);
    assert(code == NO_ERROR);
    CLogger::Get()->Write("APEX TEST", LogNotice, "Created buffer for send buffer. return code NO_ERROR : PASSED");

    ApexBuffer::SEND_BUFFER(id, sendMessage, messageSize, 0, &code);
    assert(code == NO_ERROR);
    CLogger::Get()->Write("APEX TEST", LogNotice, "Send buffer. return code NO_ERROR : PASSED");

    ApexBuffer::RECEIVE_BUFFER(id, 0, &receiveMessage, &messageSize, &code);
    assert(code == NO_ERROR);
    CLogger::Get()->Write("APEX TEST", LogNotice, "Receive buffer. return code NO_ERROR : PASSED");
    assert(*receiveMessage == *sendMessage);
    CLogger::Get()->Write("APEX TEST", LogNotice, "Receive buffer is = Test. return code NO_ERROR : PASSED");
}