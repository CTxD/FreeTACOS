#ifndef FREETACOS_PROCESSES_H
#define FREETACOS_PROCESSES_H

vector<processes> vec = {};

class processes {
    static char[] name;
    static char[] entry_point;
    static unsigned int stack_size;
    static int base_priority;
    static int period;
    static int time_capacity;
    static int deadline;
    int current_priority;
    int deadline_time;
    auto process_state;
    int processor_core_affinity;

    processes()
    {
    }

    void GET_PROCESS_STATUS()
    {
        return process_state;
    }

    void CREATE_PROCESS()
    {
        /*The CREATE_PROCESS service request creates a process and returns an
identifier that denotes the created process.*/
        return;
    }

    void SET_PRIORITY(int p)
    {
        current_priority = p;
    }

    void SUSPEND_SELF()
    {
        /*The SUSPEND_SELF service request suspends the execution of the current
process, if aperiodic. The process remains suspended until the RESUME service
request is issued or the specified time-out value expires.*/
    }

    void SUSPEND()
    {
        /*error
 when (insufficient storage capacity for the creation of the specified
 process or maximum number of processes have been created) =>
 RETURN_CODE := INVALID_CONFIG;
 when (the process named ATTRIBUTES.NAME is already created for */
    }

    void RESUME()
    {
        /*error
 when (insufficient storage capacity for the creation of the specified
 process or maximum number of processes have been created) =>
 RETURN_CODE := INVALID_CONFIG;
 when (the process named ATTRIBUTES.NAME is already created for */
    }

    void STOP_SELF()
    {
        /*error
 when (insufficient storage capacity for the creation of the specified
 process or maximum number of processes have been created) =>
 RETURN_CODE := INVALID_CONFIG;
 when (the process named ATTRIBUTES.NAME is already created for */
    }

    void STOP()
    {
        /*procedure SET_PRIORITY
         (PROCESS_ID : in PROCESS_ID_TYPE;
         PRIORITY : in PRIORITY_TYPE;
         RETURN_CODE : out RETURN_CODE_TYPE) is*/
    }

    void START()
    {
        /*procedure SUSPEND_SELF
 (TIME_OUT : in SYSTEM_TIME_TYPE;
 RETURN_CODE : out RETURN_CODE_TYPE) is
error
 when (current process owns a mutex or
 current process is error handler process) =>
 RETURN_CODE := INVALID_MODE;
 when (TIME_OUT is out of range) =>
 -- e.g., calculation causes overflow of underlying clock
 RETURN_CODE := INVALID_PARAM;
 when (process is periodic) =>
 RETURN_CODE := INVALID_MODE;*/
    }

    void DELAYED_START()
    {
    }

    void LOCK_PREEMPTION()
    {
    }

    void UNLOCK_PREEMPTION()
    {
    }

    void GET_MY_ID()
    {
        return name;
    }

    void INITIALIZE_PROCESS_CORE_AFFINITY()
    {
    }

    void GET_MY_PROCESSOR_CORE_ID()
    {
    }
};

#endif // FREETACOS_PROCESSES_H
