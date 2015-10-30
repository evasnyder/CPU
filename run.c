#include "queue.c"
#include "pqueue.c"
#include "run.h"
#include "distribution.c"

int clock_time = 0;

// event queue is the to do list

// pass processes?
void runCPU(int runtime, int numCPUS, int contextSwitch, int Quantum) {

  // create an array of structs for the CPUS
  Struct CPU cpu = initializeCPUS(numCPUS);

  // while there is still runtime left in the CPU
  while (clock_time <= runtime) {
    // if there are events in the queue...
      // DEQUEUE an event from the event queue
      Event event = removeNode();

      // UPDATE clock to the priority of the dequeued event
      clock_time = event -> timeStamp;

      if(event -> type == 1) {
        // create a new process
        createNewProcess(clock_time);

      } else if (event -> type == 2) {
        // go to ready queue
        schedulingDecision(event, clock_time);

      } else if (event -> type == 3) {
        // terminate a process

      } else if (event -> type == 4) {
        // go to IO

      } else if (event -> type == 5) {
        // quantum expire

      } else if (event -> type == 6) {
        // return from IO

      } else {
        return;
      }
      // CHECK to see if there are any new processes that should be added (i.e interarrival time)
        // call create process

        // EXECUTE the event type of the event

        // IF the event type is create -> move to the ready queue

        // FOR loop through the CPUs and if they're idle, have a process go on to it...
          // ?? HOW DOES A PROCESS GO ON TO A CPU IN CODE ??

        // MOVE from the ready queue to the CPU if there are idle CPUS

        // ROUND ROBIN ALGORITHM TO MOVE FROM READY QUEUE TO CPU

        // ADD context switch amount onto the quantum for the process

          // CHECK to see if any of the events on the CPU should be removed - CALL REMOVE PROCESS

            // terminate: free memory + update statistics
              // if CPU > clock time

              // IO: generate an event to go back to the ready queue
              // if burst < quantum

              // Quantum Expires: go back to ready queue
              // if CPU > burst > quantum
  }
}

Struct[] initializeCPUS(int num) {
  Struct CPU cpu [num];
  int i;
  for (i = 0; i < num; i++) {
    cpu[i] = (struct CPU*)malloc(sizeof(struct CPU));
  }
  return cpu;
}

void createNewProcess(Event event, int timeStamp) {
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

  enqueue(newEvent);

  // send directly to the ready queue to be placed in the running to go on the CPU
  add(newEvent);
}

void schedulingDecision(Event event, int contextSwitch, Struct CPUs, int numCPUs, int quantum) {
  struct Event* newEvent = (struct Event*)malloc(sizeof(struct Event));
  newEvent -> process = event -> process;
  free(event);

  // check to see if any CPUs are idle
  int i;
  for (i = 0; i < numCPUs; i++) {
    if (CPUs[i] -> idle == 0) {
      // if the CPU is free - put a process on it

      // mark the CPU as full
      CPUs[i] -> idle = 1;

      // generate a new event to remove it from the CPU

      if ( (process -> cpu_service_time_remaining) < quantum ) {
        // check to see if the process on the CPU should be terminated next
        // generate the time that the process should be terminated at
        newEvent -> timeStamp = clock_time + (process -> cpu_service_time_remaining);
        newEvent -> type = 3;
        newEvent -> process -> CPU_running_on = i;

        // put onto the event queue
        add(newEvent);
      } else if ( (process -> burst_time) < quantum){
        // check to see if the process on the CPU should go to IO
        newEvent -> timeStamp = clock_time + (process -> burst_time);
        newEvent -> type = 6; // return from IO aka go back to ready queue
        newEvent -> process -> CPU_running_on = i;
        // put onto the event queue
        add(newEvent);
      } else if ( (process -> cpu_service_time_remaining) > (process -> burst_time) > quantum ) {
        // check to see if the process on the CPU quantum expires
        newEvent -> timeStamp = clock_time + quantum + contextSwitch;
        newEvent -> type = 2;
        newEvent -> process -> CPU_running_on = i;
        // put onto the event queue
        add(newEvent);
      }
    }
  }
}

void removeProcess(int type, Event event, Struct CPUs) {
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

      // WHEN DO I FREE UP THE CPU ???

      // enqueue onto the event queue
      add(newEvent);
      break;

    // quantum expire
    case 6:
      // update information for the event

      // go back to the ready queue
      enqueue(event);
      break;
  }

}

/**
* Method to generate the random numbers for the process being created
* 1 =
* 2 =
* 3 =
*/
Process generateRandomValues(int processType, Process process) {

  switch(processType){
    // first process type
    case 1:
      // calculte CPU service time
      // process -> cpu_service_time =
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
