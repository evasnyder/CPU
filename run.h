#include <stdio.h>

struct Event {
  int timeStamp;
  int type;
  struct Event *next;
    // create a process of x type == 1
    // schedulingDecision = 2
    // remove a process
      // terminate == 4
      // go to IO == 5
      // quantum expire == 6
    // return from IO == 7
  struct Process *process;
  int process_type;
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

  int start_time;

  struct Process *next;

};

struct CPU {
  // 0 = idle
  // 1 = busy
  int idle;

  // STATISTICS
  int active_time;
  int context_switch_time;
  int idle_time;
};

struct Statistics {
  int len_simulation_time;
  int num_events_processed;
  int num_processes_complete;
  int final_len_event_queue;
  int avg_len_event_queue;
  int final_len_ready_queue;
  int avg_len_ready_queue;

  int total_event_queue_lengths;
  int num_event_queue_changed;

  int total_ready_queue_lengths;
  int num_ready_queue_changed;
};

struct batch {
  int cpuTime, burstTime, interArrTime, IOTime;
  int numCompleted, throughput, lastProcessTime, longestProcessTime, avgTurnaroundTime;
};
struct interactive {
  int cpuTime, burstTime, interArrTime, IOTime;
  int numCompleted, throughput, lastProcessTime, longestProcessTime, avgTurnaroundTime;
};

void runCPU(int runtime, int numCPUS, int contextSwitch, int quantum);

void createNewProcess(struct Event *event, int timeStamp, struct Statistics *stats, int proess_type);

void schedulingDecision(struct Event *event, int contextSwitch, struct CPU *CPUs, int numCPUs, int quantum, struct Statistics *stats);

void removeProcess(int type, struct Event *event, struct CPU *CPUs, int contextSwitch, struct Statistics *stats);

struct Process* generateRandomValues(int processType, struct Process* process);

void saveAvgValue(int process_type, int avgCPU, int avgBurst, int avgInterArrival, int avgIO);

void initializeCPUS(struct CPU *cpu);
