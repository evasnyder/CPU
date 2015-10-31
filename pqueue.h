// #ifdef pqueue_h_
#include <stdio.h>

//function signatures for the main Priority Queue methods

int sizePQ();
int getFirst();
struct Event* deletePQ();
//event deletePQ();
int isEmptyPQ();
void printPQ();
void add(struct Event* newEvent);

// #endif
