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
  enqueue(newEvent);
}

void removeProcess(int type) {
  switch(type) {
    // terminate
    // update statistics
    case 2:

    break;

    // go to IO
    case 3:

    break;

    // quantum expire
    case 4:

    break;
  }

}

void generateRandomValues() {

}
