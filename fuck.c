#include "queue.c"
#include "pqueue.c"
#include "fuck.h"


void createEvent(timeStamp, type, process) {
  // create a new Event
  struct Event* newEvent = (struct Event*)malloc(sizeof(struct Event));

  // create a new Process
  struct Process* newProcess = (struct Process*)malloc(sizeof(struct Process));

  // know the average values, use those average values to make own values
  // set its values to the right things
    // io service, interarrival, burst, cpu service

  // set the event type

  // an event needs to be created and added to the event queue based off of priority
  add(newEvent);
}

void removeProcess(int type, Event event) {
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
void generateRandomValues(int processType) {

}
