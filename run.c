#include "queue.h"
#include "pqueue.h"
#include "run.h"
#include "distribution.h"
#include <stdlib.h>

int clock_time = 0;
struct batch* avgBatchValues;
struct interactive* avgInteractiveValues;


//one cannot return array in C, only a pointer to the array
void initializeCPUS(struct CPU *cpu) {
  //struct CPU cpu;
  cpu = (struct CPU*)malloc(sizeof(struct CPU));
  cpu -> idle = 0;
  //return cpu;
}

void runCPU(int runtime, int numCPUS, int contextSwitch, int quantum) {

  printf("ENTERING RUN \n");
  printf("Run Time %d\n", runtime);
  printf("numCPUS %d\n", numCPUS);
  printf("contextSwitch %d\n", contextSwitch);
  printf("quantum %d\n", quantum);

  int beginning = 1;

  struct Statistics* stats = (struct Statistics*)malloc(sizeof(struct Statistics));

  printf("made stats\n");

  // create an array of structs for the CPUS
  struct CPU cpu_array[numCPUS];

  int i;
  for ( i = 0; i < numCPUS; ++i)
  {
    printf("initializing CPU\n");
     //cpu_array[i] = *(struct CPU*)malloc(sizeof(struct CPU));
     //cpu_array->idle = 0;
    initializeCPUS(&cpu_array[i]);
    //  printf( "r[%d] = %d\n", i, cpu_array[i]);

  }

  printf("after for loop\n");

  // while there is still runtime left in the CPU
  while (clock_time <= runtime) {
    printf("In the while loop \n");

    // if there are events in the queue...
      // DEQUEUE an event from the event queue
      if(!isEmptyPQ()) {
        printf("queue is not empty\n");
        struct Event *event = delete();
        printf("Event type %d\n", event -> type);
        // UPDATE clock to the priority of the dequeued event
        clock_time = event -> timeStamp;

        if(event -> type == 1) {
          printf("event type is to create a new process\n");
          // create a new process
          createNewProcess(event, clock_time, stats, event -> process_type);
        } else if (event -> type == 2) {
          printf("event type is to make a decision\n");
          schedulingDecision(event, contextSwitch, cpu_array, numCPUS, quantum, stats);
        } else if (event -> type == 4 || event -> type == 5 || event -> type == 6) {
          printf("event type is to remove something from the CPU\n");
          removeProcess(event -> type, event, cpu_array, contextSwitch, stats);
        } else {
          return;
        }
      } else {
          if(beginning == 1) {
            // struct Event* newEvent = (struct Event*)malloc(sizeof(struct Event));
            // createNewProcess(newEvent, clock_time, stats, newEvent -> process_type);
            beginning = 0;
          }
      }
  }

  stats -> len_simulation_time = runtime;
  stats -> final_len_event_queue = sizePQ();
  stats -> final_len_ready_queue = sizeQ();
  stats -> avg_len_event_queue = (stats -> total_event_queue_lengths) / (stats -> num_event_queue_changed);
  stats -> avg_len_ready_queue = (stats -> total_ready_queue_lengths) / (stats -> num_ready_queue_changed);

}



void createNewProcess(struct Event *event, int timeStamp, struct Statistics *stats, int process_type) {
  // create a new Process
  struct Process *newProcess = (struct Process*)malloc(sizeof(struct Process));
  // create a new Event
  struct Event* newEvent = (struct Event*)malloc(sizeof(struct Event));

  newProcess = generateRandomValues(process_type, *newProcess);
  newProcess -> start_time = clock_time;

  struct Event* interarrivalProcessTime = (struct Event*)malloc(sizeof(struct Event));
  interarrivalProcessTime = clock_time + newProcess -> interarrival_time;
  interarrivalProcessTime -> type = 1;
  interarrivalProcessTime -> process_type = process_type;
  enqueue(interarrivalProcessTime);

  free(event);

  // set the event type - scheduling decision
  newEvent -> type = 2;
  newEvent -> process = newProcess;

  // add event to the event queue
  add(newEvent);

  stats -> total_event_queue_lengths = stats -> total_event_queue_lengths + sizePQ();
  stats -> num_event_queue_changed = (stats -> num_event_queue_changed) + 1;
}

void schedulingDecision(struct Event *event, int contextSwitch, struct CPU *CPUs, int numCPUs, int quantum, struct Statistics *stats) {
  // add the new event to the ready queue
  enqueue(event);

  // check to see if any CPUs are idle
  int i;
  for (i = 0; i < numCPUs; i++) {
    if (CPUs[i].idle == 0) {
      struct Event* newEvent = (struct Event*)malloc(sizeof(struct Event));
      struct Process* tempProcess = (struct Process*)malloc(sizeof(struct Process));
      tempProcess = event -> process;
      newEvent -> process = tempProcess;
      free(event);

      // if the CPU is free - put a process on it ==> ROUND ROBIN HERE TO KNOW WHICH ONE

      // mark the CPU as full
      CPUs[i].idle = 1;

      // generate a new event to remove it from the CPU

      if ( (newEvent -> process -> cpu_service_time_remaining) < quantum ) {
        // check to see if the process on the CPU should be terminated next
        // generate the time that the process should be terminated at
        newEvent -> timeStamp = clock_time + (newEvent -> process  -> cpu_service_time_remaining);
        newEvent -> type = 4;
        newEvent -> process  -> CPU_running_on = i;

        // put onto the event queue
        add(newEvent);
        stats -> total_event_queue_lengths = (stats -> total_event_queue_lengths) + sizePQ();
        stats -> num_event_queue_changed = (stats -> num_event_queue_changed) + 1;

      } else if ( (newEvent -> process  -> burst_time) < quantum){
        // check to see if the process on the CPU should go to IO

        newEvent -> timeStamp = clock_time + (newEvent -> process -> burst_time);
        newEvent -> type = 5; // return from IO aka go back to ready queue
        newEvent -> process -> CPU_running_on = i;
        // put onto the event queue
        add(newEvent);
        stats -> total_event_queue_lengths = (stats -> total_event_queue_lengths) + sizePQ();
        stats -> num_event_queue_changed = (stats -> num_event_queue_changed) + 1;

      } else if ( (newEvent -> process -> cpu_service_time_remaining) > (newEvent -> process  -> burst_time) > quantum ) {
        // check to see if the process
        // on the CPU quantum expires
        newEvent -> timeStamp = clock_time + quantum + contextSwitch;
        newEvent -> type = 6;
        tempProcess -> CPU_running_on = i;
        // put onto the event queue
        add(newEvent);
        stats -> total_event_queue_lengths = (stats -> total_event_queue_lengths) + sizePQ();
        stats -> num_event_queue_changed = (stats -> num_event_queue_changed) + 1;
      }
    }
  }
}

void removeProcess(int type, struct Event *event, struct CPU *CPUs, int contextSwitch, struct Statistics *stats) {
  // clock is equal to the time stamp (i.e priority) from the process being removed
  // from the event queue
  struct Event* newEvent;
  switch(type) {
    // terminate
    case 4:
      switch(event->process_type) {
        case 1:
          // batch process
          avgBatchValues -> numCompleted = avgBatchValues -> numCompleted + 1;
          // if the process that just finished was running for the longest time
          if (clock_time - (event -> process -> start_time) > avgBatchValues -> longestProcessTime) {
            avgBatchValues -> longestProcessTime = (clock_time - (event->process->start_time));
          }
          break;
        case 2:
          // batch process
          avgInteractiveValues -> numCompleted = avgInteractiveValues -> numCompleted + 1;
          if (clock_time - (event -> process -> start_time) > avgInteractiveValues -> longestProcessTime) {
            avgInteractiveValues -> longestProcessTime = (clock_time - (event->process->start_time));
          }
          break;
      }

      // update statistics
      CPUs[event -> process -> CPU_running_on].idle= 0;
      free(event);
      // free event from memory
      break;

    // go to IO
    case 5:
      // generate a new event to go back to the ready queue
      newEvent = (struct Event*)malloc(sizeof(struct Event));
      newEvent -> process = event -> process;
      // call schedulingDecision after clock_time + io service time
      // i.e go back to the ready queue after the time on the IO has been completed
      newEvent -> timeStamp = clock_time + (newEvent -> process -> IO_Service);

      // go back to the schedulingDecision afterwards
      newEvent -> type = 2;

      CPUs[event -> process -> CPU_running_on].idle = 0;

      free(event);
      // enqueue onto the event queue
      add(newEvent);
      stats -> total_event_queue_lengths = stats -> total_event_queue_lengths + sizePQ();
      stats -> num_event_queue_changed = (stats -> num_event_queue_changed) + 1;
      break;

    // quantum expire
    case 6:
      // update information for the event
      newEvent = (struct Event*)malloc(sizeof(struct Event));
      newEvent -> process = event -> process;
      newEvent -> timeStamp = clock_time + contextSwitch;
      newEvent -> type = 2;

      CPUs[event -> process -> CPU_running_on].idle = 0;

      free(event);
      // go back to the event queue
      add(newEvent);
      stats -> total_event_queue_lengths = stats -> total_event_queue_lengths + sizePQ();
      stats -> num_event_queue_changed = (stats -> num_event_queue_changed) + 1;
      break;
  }

}

//method to save processes data from the input file
void saveAvgValue(int process_type, int avgCPU, int avgBurst, int avgInterArrival, int avgIO) {
  printf("Saving Average Values! \n");
  avgBatchValues = (struct batch*)malloc(sizeof(struct batch));
  avgInteractiveValues = (struct interactive*)malloc(sizeof(struct interactive));
  struct Event* newEvent = (struct Event*)malloc(sizeof(struct Event));

  switch (process_type) {
    case 1:
      printf("Hey I'm a batch....\n");
      newEvent -> type = 1;
      newEvent -> process_type = 1;
      printf("adding new event from save avg values\n");
      add(&newEvent);
      printPQ();
      // batch
      avgBatchValues -> cpuTime = avgCPU;
      avgBatchValues -> burstTime = avgBurst;
      avgBatchValues -> interArrTime = avgInterArrival;
      avgBatchValues -> IOTime = avgIO;
      avgBatchValues -> numCompleted = 0;
      avgBatchValues -> throughput = 0;
      avgBatchValues -> lastProcessTime = 0;
      avgBatchValues -> longestProcessTime = 0;
      avgBatchValues -> avgTurnaroundTime = 0;
      break;
    case 2:
      newEvent -> type = 1;
      newEvent -> process_type = 2;
      // interactive
      avgInteractiveValues -> cpuTime = avgCPU;
      avgInteractiveValues -> burstTime = avgBurst;
      avgInteractiveValues -> interArrTime = avgInterArrival;
      avgInteractiveValues -> IOTime = avgIO;
      avgInteractiveValues -> numCompleted = 0;
      avgInteractiveValues -> throughput = 0;
      avgInteractiveValues -> lastProcessTime = 0;
      avgInteractiveValues -> longestProcessTime = 0;
      avgInteractiveValues -> avgTurnaroundTime = 0;
      break;
  }
}

/**
* Method to generate the random numbers for the process being created
* 1 =
* 2 =
*/
struct Process* generateRandomValues(int processType, struct Process process) {

  switch(processType){
    // batch
    case 1:
      // calculte CPU service time
      process.cpu_service_time = *exponential_distribution((avgBatchValues -> cpuTime));
      // calculate burst time
      process.burst_time = *exponential_distribution((avgBatchValues -> burstTime));
      // calculate interarrival time
      process.interarrival_time = *exponential_distribution((avgBatchValues -> interArrTime));
      // calculate IO service time
      process.IO_Service = *exponential_distribution((avgBatchValues -> IOTime));

      return &process;

    // interactive
    case 2:
      // calculte CPU service time
      process.cpu_service_time = *exponential_distribution((avgInteractiveValues -> cpuTime));
      // calculate burst time
      process.burst_time = *exponential_distribution((avgInteractiveValues -> burstTime));
      // calculate interarrival time
      process.interarrival_time = *exponential_distribution((avgInteractiveValues -> interArrTime));
      // calculate IO service time
      process.IO_Service = *exponential_distribution((avgInteractiveValues -> IOTime));
      return &process;
  }
}
