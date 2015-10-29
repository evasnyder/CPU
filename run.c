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
        goToReadyQueue(event, clock_time);

      } else if (event -> type == 3) {
        // go to CPU

      } else if (event -> type == 4) {
        // terminate a process

      } else if (event -> type == 5) {
        // go to IO

      } else if (event -> type == 6) {
        // quantum expire

      } else if (event -> type == 7) {
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

Event createNewProcess(Event event, int timeStamp) {
  // create a new Process
  struct Process* newProcess = (struct Process*)malloc(sizeof(struct Process));
  // create a new Event
  struct Event* newEvent = (struct Event*)malloc(sizeof(struct Event));

  // know the average values, use those average values to make own values
  // set its values to the right things
    // io service, interarrival, burst, cpu service

  free(event);

  // set the event type - GO TO READY QUEUE
  newEvent -> type = 2;
  newEvent -> timeStamp = clock_time;
  return newEvent;
}

void goToReadyQueue(Event event, int contextSwitch) {
  struct Event* newEvent = (struct Event*)malloc(sizeof(struct Event));
  newEvent -> process = event -> process;
  free(event);

  // next step is to go to the CPU i.e add the context switch time to the clock time
  // CALCUALTE TIME STAMP FOR ALGORITHM HERE ?????
  newEvent -> type = 3;
  newEvent -> timeStamp = clock_time + contextSwitch;

  enqueue(newEvent);
}

void goToCPU(Event event, int clock_time) {
  struct Event* newEvent = (struct Event*)malloc(sizeof(struct Event));
  newEvent -> process = event -> process;
  free(event);

  // if it is on the CPU you need to then see if you need to remove it.....
  // calculations need to be done to see what remove should be completed

  // check to see if the process on the CPU should be terminated next
  // check to see if the process on the CPU should go to IO
  // check to see if the process on the CPU quantum expires

}

void removeProcess(int type, Event event) {
  // clock is equal to the time stamp (i.e priority) from the process being removed
  // from the event queue
  switch(type) {
    // terminate
    case 2:
      // free event from memory

      // update statistics

      break;

    // go to IO
    case 3:
      // generate a new event to go back to the ready queue
      struct Event* newEvent = (struct Event*)malloc(sizeof(struct Event));

      // initialize new Event...
      // newEvent -> timeStamp =
      // newEvent -> type =
      // set the process of the new event point to the event of the current process
      newEvent -> process = event -> process;

      // enqueue onto the ready queue
      enqueue(newEvent);
      break;

    // quantum expire
    case 4:
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
