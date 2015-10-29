
struct Event {
  int timeStamp;
  int type;
    // create a process of x type == 1
    // remove a process
      // terminate == 2
      // go to IO == 3
      // quantum expire == 4
    // return from IO == 5
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
};


void createEvent(timeStamp, type, process);

void removeProcess();
