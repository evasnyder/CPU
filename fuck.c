#include "queue.c"
#include "pqueue.c"
#include "fuck.h"
#include "distribution.c"

int clock = 0;

void runCPU(int runtime) {
  // while there is still runtime left in the CPU
  while (runtime >= 0) {
    // dequeue from the PQ and do whatever its task is
  }
}

void createNewProcess(timeStamp, type) {
  // create a new Process
  struct Process* newProcess = (struct Process*)malloc(sizeof(struct Process));

  // create a new Event
  struct Event* newEvent = (struct Event*)malloc(sizeof(struct Event));

  // know the average values, use those average values to make own values
  // set its values to the right things
    // io service, interarrival, burst, cpu service

  // set the event type
  newProcess -> type = type;

  // an event needs to be created and added to the event queue (PQ) based off of priority
  add(newEvent);
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
