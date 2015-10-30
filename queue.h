#include <stdio.h>

struct Process {
	struct Process *next_process;
	int avg_CPU_Service_Time;
	int avg_Burst_Time;
  int avg_Interarrival_Time;
  int avg_IO_Service_Time;
};

void enqueue (int value);

void dequeue();

//int peek();

int isEmpty();

void clearQueue();
