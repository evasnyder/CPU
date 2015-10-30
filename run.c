#include "queue.c"
#include "pqueue.c"
#include "run.h"
#include "distribution.c"

int clock_time = 0;

void runCPU(int runtime, int numCPUS, int contextSwitch, int quantum) {

  struct Statistics* stats = (struct Statistics*)malloc(sizeof(struct Statistics));

  // create an array of structs for the CPUS
  struct CPU cpu_array = initializeCPUS(numCPUS);

  // while there is still runtime left in the CPU
  while (clock_time <= runtime) {
    // if there are events in the queue...
      // DEQUEUE an event from the event queue
      Event event = removeNode();

      // UPDATE clock to the priority of the dequeued event
      clock_time = event -> timeStamp;

      if(event -> type == 1) {
        // create a new process
        createNewProcess(event, clock_time, stats);
      } else if (event -> type == 2) {
        schedulingDecision(event, contextSwitch, cpu_array, numCPUS, quantum);
      } else if (event -> type == 4 || event -> type == 5 || event -> type == 6) {
        removeProcess(event -> type, event, cpu_array, contextSwitch);
      } else {
        return;
      }
  }

  stats -> len_simulation_time = runtime;
  stats -> final_len_event_queue = sizePQ();
  stats -> final_len_ready_queue = sizeQ();
  stats -> avg_len_event_queue = total_event_queue_lengths / num_event_queue_changed;
  stats -> avg_len_ready_queue = total_ready_queue_lengths / num_ready_queue_changed;

}

struct[] initializeCPUS(int num) {
  struct CPU cpu [num];
  int i;
  for (i = 0; i < num; i++) {
    cpu[i] = (struct CPU*)malloc(sizeof(struct CPU));
  }
  return cpu;
}

void createNewProcess(struct Event *event, int timeStamp, struct Statistics *stats) {
  // create a new Process
  struct Process* newProcess = (struct Process*)malloc(sizeof(struct Process));
  // create a new Event
  struct Event* newEvent = (struct Event*)malloc(sizeof(struct Event));

  // know the average values, use those average values to make own values
  // set its values to the right things
    // io service, interarrival, burst, cpu service

  free(event);

  // set the event type - scheduling decision
  newEvent -> type = 2;
  newEvent -> process = newProcess;

  // add event to the event queue
  add(newEvent);

  stats -> total_event_queue_lengths = stats -> total_event_queue_lengths + sizePQ();
  stats -> num_event_queue_changed = (stats -> num_event_queue_changed) + 1;
}

void schedulingDecision(struct Event *event, int contextSwitch, struct CPU *CPUs, int numCPUs, int quantum) {
  // add the new event to the ready queue
  enqueue(event);

  // check to see if any CPUs are idle
  int i;
  for (i = 0; i < numCPUs; i++) {
    if (CPUs[i] -> idle == 0) {
      struct Event* newEvent = (struct Event*)malloc(sizeof(struct Event));
      newEvent -> process = event -> process;
      free(event);

      // if the CPU is free - put a process on it ==> ROUND ROBIN HERE TO KNOW WHICH ONE

      // mark the CPU as full
      CPUs[i] -> idle = 1;

      // generate a new event to remove it from the CPU

      if ( (process -> cpu_service_time_remaining) < quantum ) {
        // check to see if the process on the CPU should be terminated next
        // generate the time that the process should be terminated at
        newEvent -> timeStamp = clock_time + (process -> cpu_service_time_remaining);
        newEvent -> type = 4;
        newEvent -> process -> CPU_running_on = i;

        // put onto the event queue
        add(newEvent);
        stats -> total_event_queue_lengths = stats -> total_event_queue_lengths + sizePQ();
        stats -> num_event_queue_changed = (stats -> num_event_queue_changed) + 1;

      } else if ( (process -> burst_time) < quantum){
        // check to see if the process on the CPU should go to IO
        newEvent -> timeStamp = clock_time + (process -> burst_time);
        newEvent -> type = 5; // return from IO aka go back to ready queue
        newEvent -> process -> CPU_running_on = i;
        // put onto the event queue
        add(newEvent);
        stats -> total_event_queue_lengths = stats -> total_event_queue_lengths + sizePQ();
        stats -> num_event_queue_changed = (stats -> num_event_queue_changed) + 1;

      } else if ( (process -> cpu_service_time_remaining) > (process -> burst_time) > quantum ) {
        // check to see if the process on the CPU quantum expires
        newEvent -> timeStamp = clock_time + quantum + contextSwitch;
        newEvent -> type = 6;
        newEvent -> process -> CPU_running_on = i;
        // put onto the event queue
        add(newEvent);
        stats -> total_event_queue_lengths = stats -> total_event_queue_lengths + sizePQ();
        stats -> num_event_queue_changed = (stats -> num_event_queue_changed) + 1;
      }
    }
  }
}

void removeProcess(int type, Event event, struct CPU *CPUs, int contextSwitch) {
  // clock is equal to the time stamp (i.e priority) from the process being removed
  // from the event queue
  switch(type) {
    // terminate
    case 4:
      // update statistics
      CPUs[process -> CPU_running_on] = 0;
      free(event)
      // free event from memory
      break;

    // go to IO
    case 5:
      // generate a new event to go back to the ready queue
      struct Event* newEvent = (struct Event*)malloc(sizeof(struct Event));
      newEvent -> process = event -> process;
      // call schedulingDecision after clock_time + io service time
      // i.e go back to the ready queue after the time on the IO has been completed
      newEvent -> timeStamp = clock_time + (newEvent -> process -> IO_Service);

      // go back to the schedulingDecision afterwards
      newEvent -> type = 2;

      CPUs[process -> CPU_running_on] = 0;

      free(event);
      // enqueue onto the event queue
      add(newEvent);
      stats -> total_event_queue_lengths = stats -> total_event_queue_lengths + sizePQ();
      stats -> num_event_queue_changed = (stats -> num_event_queue_changed) + 1;
      break;

    // quantum expire
    case 6:
      // update information for the event
      struct Event* newEvent = (struct Event*)malloc(sizeof(struct Event));
      newEvent -> process = event -> process;
      newEvent -> timeStamp = clock_time + contextSwitch;
      newEvent -> type = 2;

      CPUs[process -> CPU_running_on] = 0;

      free(event);
      // go back to the event queue
      add(newEvent);
      stats -> total_event_queue_lengths = stats -> total_event_queue_lengths + sizePQ();
      stats -> num_event_queue_changed = (stats -> num_event_queue_changed) + 1;
      break;
  }

}

/**
* Method to generate the random numbers for the process being created
* 1 =
* 2 =
* 3 =
*/
Process generateRandomValues(int processType, struct Process *process) {

  switch(processType){
    // first process type
    case 1:
      // calculte CPU service time
      // process -> cpu_service_time = exponential_distribution
      // calculate burst time

      // calculate interarrival time

      // calculate IO service time
      return process;
      break;

    case 2:
      // calculte CPU service time

      // calculate burst time

      // calculate interarrival time

      // calculate IO service time
      return process;
      break;

    case 3:
      // calculte CPU service time

      // calculate burst time

      // calculate interarrival time

      // calculate IO service time
      return process;
      break;
  }
}
