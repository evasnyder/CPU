#include <stdio.h>

struct Event {
  int timeStamp;
  int type;
    // create a process of x type == 1
    // schedulingDecision = 2
    // remove a process
      // terminate == 4
      // go to IO == 5
      // quantum expire == 6
    // return from IO == 7
  struct Process *process;
};

struct Process {
  // how long I'm stuck in the IO
  int IO_Service;

  // Next time at which a new process will arrive
  int interarrival_time;

  // how long it wants to run before going to IO
  int burst_time;

  // total time on the CPU in the lifetime of the process
  int cpu_service_time;

  // how much burst time there is remaining
  int burst_time_remaining;

  // how much cpu service time there is left for the process
  int cpu_service_time_remaining;

  int CPU_running_on;
};

struct CPU {
  // 0 = idle
  // 1 = busy
  int idle = 0;
};


void createEvent(timeStamp, type, process);

void removeProcess();

void generateRandomValues();
