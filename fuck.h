
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
}

struct Process {
  int IO_Service;
  int interarrival_time;
  int burst_time;
  int cpu_service_time;

  int burst_time_remaining;
  int cpu_service_time_remaining;
}


void createEvent(timeStamp, type, process);
