#ifdef pqueue_h_
#include <stdio.h>

//function signatures for the main Priority Queue methods
void add(struct Event* newEvent);
int sizePQ();
int getFirst();
struct Event deletePQ();
int isEmptyPQ();
void printPQ();

#endif
