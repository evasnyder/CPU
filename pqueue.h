#include <stdio.h>

struct Process {
	struct Process *next_process;
	int avg_CPU_Service_Time;
	int avg_Burst_Time;
  int avg_Interarrival_Time;
  int avg_IO_Service_Time;
};

int add (int new_value, int new_priority);

int removeNode (int new_priority);

int contains(int new_priority);

void printQueue();

int peek();

int isEmpty();

void clearQueue();
