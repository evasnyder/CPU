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
  cpu -> context_switch_time = 0;
  //return cpu;
}

/*
* Method to run the CPU scheduler!
* Calls all of the necessary methods to make our CPU scheduler work.
*/
void runCPU(int runtime, int numCPUS, int contextSwitch, int quantum) {

  struct Statistics* stats = (struct Statistics*)malloc(sizeof(struct Statistics));
  stats -> len_simulation_time = 0;
  stats -> num_processes_complete = 0;
  stats -> final_len_event_queue = 0;
  stats -> avg_len_event_queue = 0;
  stats -> final_len_ready_queue = 0;
  stats -> avg_len_ready_queue = 0;

  stats -> total_event_queue_lengths = 0;
  stats -> num_event_queue_changed = 0;

  stats -> total_ready_queue_lengths = 0;
  stats -> num_ready_queue_changed = 0;

  stats -> num_events_processed = 0;

  // create an array of structs for the CPUS
  struct CPU cpu_array[numCPUS];

  //initialize CPU array
  int i;
  for ( i = 0; i < numCPUS; ++i)
  {
    initializeCPUS(&cpu_array[i]);

  }


  // while there is still runtime left in the CPU
  while (clock_time <= runtime) {


    if(clock_time > runtime) {
      break;
    }

    // if there are events in the queue...
      // DEQUEUE an event from the event queue
      if(isEmptyPQ() == 0) {
      //  struct Event *event = deletePQ();
        struct Event *event = malloc(sizeof(struct Event));
        event -> type = 0;
        event = deletePQ();

        if(event -> type == NULL) {
          printf("event is null\n");
        } 

        else {
          printf("event is not null, trying to access type\n");

        }

        // UPDATE clock to the priority of the dequeued event
        clock_time = event -> timeStamp;

        if(event -> type == 1) {

          // create a new process
          createNewProcess(event, clock_time, stats, event -> process_type);

           ++(stats -> num_events_processed);

        } 

        else if (event -> type == 2) {

          schedulingDecision(event, contextSwitch, cpu_array, numCPUS, quantum, stats);

          ++(stats -> num_events_processed);
        } 

        else if (event -> type == 4 || event -> type == 5 || event -> type == 6) {

          removeProcess(event -> type, event, cpu_array, contextSwitch, stats);

          ++(stats -> num_events_processed);
        }

      } 

      else {
        printf("Event Queue is empty! No more processes to exectue\n");

        break;
      }
  }

  //print out stats
  stats -> len_simulation_time = clock_time;
  printf("length of simulation time: %d\n", stats -> len_simulation_time);
  printf("number of events processed: %d\n", stats -> num_events_processed);

  stats -> final_len_event_queue = sizePQ();
  printf("final event queue length %d\n", stats -> final_len_event_queue);

  stats -> final_len_ready_queue = sizeQ();
  printf("final ready queue length %d\n", stats -> final_len_ready_queue);

  stats -> avg_len_event_queue = (stats -> total_event_queue_lengths) / (float)(stats -> num_event_queue_changed);
  printf("average length event queue %d\n", stats -> avg_len_event_queue);

  stats -> avg_len_ready_queue = (stats -> total_ready_queue_lengths) / (float)(stats -> num_ready_queue_changed);

  printf("average length ready queue %d\n", stats -> avg_len_ready_queue);
  printf("number of batch processes completed: %d\n", avgBatchValues -> numCompleted);
  printf("number of interactive processes completed: %d\n", avgInteractiveValues -> numCompleted);

  



}


/*
* Method to create a new process and add it to the ready queue as well as creating
* and event to put another process onto the event queue.
*/
void createNewProcess(struct Event *event, int timeStamp, struct Statistics *stats, int process_type) {
  

  //create a new Process
  struct Process *newProcess = (struct Process*)malloc(sizeof(struct Process));

  //create a new Event
  struct Event* newEvent = (struct Event*)malloc(sizeof(struct Event));

  newProcess = generateRandomValues(process_type, newProcess);
  newProcess -> start_time = clock_time;


  struct Event* interarrivalProcessTime = (struct Event*)malloc(sizeof(struct Event));

  interarrivalProcessTime -> timeStamp = clock_time + (newProcess -> interarrival_time);

  interarrivalProcessTime -> type = 1;

  interarrivalProcessTime -> process_type = process_type;

  add(interarrivalProcessTime);
  stats -> total_ready_queue_lengths= (stats -> total_ready_queue_lengths) + sizeQ();
        stats -> num_ready_queue_changed = (stats -> num_ready_queue_changed) + 1;

  free(event);

  // set the event type - scheduling decision
  newEvent -> type = 2;
  newEvent -> process = newProcess;

  // add event to the event queue
  add(newEvent);

  stats -> total_event_queue_lengths = stats -> total_event_queue_lengths + sizePQ();
  stats -> num_event_queue_changed = (stats -> num_event_queue_changed) + 1;
}

/*
* Method which decides if it's possible to put a process on the CPU and if so, does
* and then generates an event to later remove it and free the CPU again
*/
void schedulingDecision(struct Event *event, int contextSwitch, struct CPU *CPUs, int numCPUs, int quantum, struct Statistics *stats) {
  // add the new event to the ready queue
  enqueue(event);
  stats -> total_ready_queue_lengths= (stats -> total_ready_queue_lengths) + sizeQ();
        stats -> num_ready_queue_changed = (stats -> num_ready_queue_changed) + 1;

  // check to see if any CPUs are idle
  int i;
  for (i = 0; i < numCPUs; i++) {

    if (CPUs[i].idle == 0) {
      struct Event* newEvent = (struct Event*)malloc(sizeof(struct Event));
      struct Process* tempProcess = (struct Process*)malloc(sizeof(struct Process));
      tempProcess = event -> process;
      newEvent -> process = tempProcess;
      newEvent -> process -> cpu_service_time_remaining = event -> process -> cpu_service_time_remaining;
     

      // mark the CPU as full
      CPUs[i].idle = 1;
      CPUs[i].context_switch_time = CPUs[i].context_switch_time + contextSwitch;

      // generate a new event to remove it from the CP
      if ( (event -> process -> cpu_service_time_remaining) < quantum ) {

        // check to see if the process on the CPU should be terminated next
        // generate the time that the process should be terminated at
        newEvent -> timeStamp = clock_time + (event -> process  -> cpu_service_time_remaining);
      
        newEvent -> type = 4;
        newEvent -> process  -> CPU_running_on = i;
        newEvent -> process -> cpu_service_time_remaining = 0;

        // put onto the event queue
        add(newEvent);
        stats -> total_event_queue_lengths = (stats -> total_event_queue_lengths) + sizePQ();
        stats -> num_event_queue_changed = (stats -> num_event_queue_changed) + 1;
      } 

      else if ( (event -> process -> burst_time) < quantum){

        // check to see if the process on the CPU should go to IO
        newEvent -> timeStamp = clock_time + (event -> process -> burst_time);
        newEvent -> type = 5; // return from IO aka go back to ready queue
        newEvent -> process -> CPU_running_on = i;
        newEvent -> process -> cpu_service_time_remaining = (event -> process -> cpu_service_time_remaining) - (event -> process -> burst_time);

        // put onto the event queue
        add(newEvent);
        stats -> total_event_queue_lengths = (stats -> total_event_queue_lengths) + sizePQ();
        stats -> num_event_queue_changed = (stats -> num_event_queue_changed) + 1;
      } 

      else if ( (event -> process -> cpu_service_time_remaining) > quantum ) {
        // check to see if the process
        // on the CPU quantum expires
        newEvent -> timeStamp = clock_time + quantum + contextSwitch;
        newEvent -> type = 6;
        tempProcess -> CPU_running_on = i;
        newEvent -> process -> cpu_service_time_remaining = (event -> process -> cpu_service_time_remaining) - (quantum + contextSwitch);
        // put onto the event queue
        add(newEvent);
        stats -> total_event_queue_lengths = (stats -> total_event_queue_lengths) + sizePQ();
        stats -> num_event_queue_changed = (stats -> num_event_queue_changed) + 1;
      } else {
        printf("Check here\n");
      }
    }
  }
}

/*
* Method to remove a process from the CPU
* depending upon clock time and values for the individual process
*/
void removeProcess(int type, struct Event *event, struct CPU *CPUs, int contextSwitch, struct Statistics *stats) {
  // clock is equal to the time stamp (i.e priority) from the process being removed
  // from the event queue
  struct Event* newEvent;

  switch(event -> type) {
    printf("inside switch\n");

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

          createNewProcess(event, clock_time, stats, 1);

          break;

        case 2:
          // batch process
          avgInteractiveValues -> numCompleted = avgInteractiveValues -> numCompleted + 1;

          if (clock_time - (event -> process -> start_time) > avgInteractiveValues -> longestProcessTime) {
            avgInteractiveValues -> longestProcessTime = (clock_time - (event->process->start_time));
          }

          createNewProcess(event, clock_time, stats, 2);
          break;
      }

      // update statistics
      CPUs[event -> process -> CPU_running_on].idle= 0;

       // free event from memory
      free(event);
     
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

  avgBatchValues = (struct batch*)malloc(sizeof(struct batch));

  avgInteractiveValues = (struct interactive*)malloc(sizeof(struct interactive));

  struct Event* newEvent = (struct Event*)malloc(sizeof(struct Event));

  switch (process_type) {

    case 1:
      newEvent -> type = 1;
      newEvent -> process_type = 1;
      add(newEvent);
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
      add(newEvent);
      printPQ();
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
* 1 = is for a batch process
* 2 = is for an interactive process
*/
struct Process* generateRandomValues(int processType, struct Process* process) {

  switch(processType){
    // batch
    case 1:
      // calculte CPU service time
      process -> cpu_service_time = *exponential_distribution((avgBatchValues -> cpuTime));
      printf("process cpu service time: %d\n", process -> cpu_service_time);
      // calculate burst time
      process -> burst_time = *exponential_distribution((avgBatchValues -> burstTime));
      printf("process burst time: %d\n", process -> burst_time);
      // calculate interarrival time
      process -> interarrival_time = *exponential_distribution((avgBatchValues -> interArrTime));
      printf("process interarrival time: %d\n", process -> interarrival_time);
      // calculate IO service time
      process -> IO_Service = *exponential_distribution((avgBatchValues -> IOTime));
      printf("process IO Service Time: %d\n", process -> IO_Service);

      process -> cpu_service_time_remaining = process -> cpu_service_time;
      return process;

    // interactive
    case 2:
      // calculte CPU service time
      process -> cpu_service_time = *exponential_distribution((avgInteractiveValues -> cpuTime));
      // calculate burst time
      process -> burst_time = *exponential_distribution((avgInteractiveValues -> burstTime));
      // calculate interarrival time
      process -> interarrival_time = *exponential_distribution((avgInteractiveValues -> interArrTime));
      // calculate IO service time
      process -> IO_Service = *exponential_distribution((avgInteractiveValues -> IOTime));

      process -> cpu_service_time_remaining = process -> cpu_service_time;


      return process;
  }
}
