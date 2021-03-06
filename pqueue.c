#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"
#include "run.h"

//declare the head Node of the Queue and set it to null
struct Event* head = NULL;
int size = 0;

//insert into the Queue by giving the element and it's priority as the parameters
//declare two temp Nodes, temp1 and temp2
//allocate memory to temp1 and set it's data and priority to be the same as the element to be inserted
//if the Queue is empty or if the priority of the element to be inserted is higher, add temp1 before the head and set it as the head
//if the Queue is not empty and the priority of the new element is lower than the head's, then traverse through the Queue until the correct position for its priority is found
void add(struct Event* newEvent)
{
    //int newElement;
    //int eventPriority  hy;
	struct Event* temp1;
	struct Event* temp2;

	temp1 = (struct Event*)malloc(sizeof(struct Event));

	//newEvent->type = newElement;
	//newEvent->timeStamp = eventPriority          ;

	//if the Queue is empty of if the element that is being inserted has a higher priority
	if (isEmptyPQ() || newEvent->timeStamp < head->timeStamp)
	{

		temp1 = head;
		head = newEvent;
		head -> next = temp1;
        size = size +1;
	}

	else {
		temp1 = head;

		while (temp1->next != NULL && temp1->next->timeStamp <= newEvent->timeStamp)
		{
			temp1 = temp1->next;
		}

		temp2 = temp1->next;
		temp1->next = newEvent;
		newEvent -> next = temp2;
        size = size +1;
	}
}

int getFirst()
{
    //printf("%s %d", "First:", head->data);
    return head->type;
}

//to delete an element, first check whether the Queue is empty. If it isn't, declare a temp Node and save the head Node to it
//declare an int variable and save head's data to it
//set the second Node in the Queue (the one after the head) as the head and free temp's memory to get rid of the previous head in memory
//return the data of the deleted head
struct Event* deletePQ() {
   struct Event *temp = malloc(sizeof(struct Event));
   if(isEmptyPQ()) printf("EMPTY\n");
   else
   { temp = head;
     head = head->next;
     --size;
   }
   return temp;
}


int sizePQ()
{
    return size;
}

//check to see whether a Queue is empty or not by returning 1 if it is and 0 if it isn't
int isEmptyPQ()
{
	if (head == NULL)
		return 1;
	else
		return 0;
}

//to print the Queue, first check whether it's empty. If it isn't, then traverse through the Queue and print out each
//Node's data and priority in the Queue
void printPQ() {
	struct Event* temp;
	temp = head;

	if (isEmptyPQ())
	{
		return;
	}

	else {
		while (temp != NULL)
		{
			temp = temp->next;
		}
	}
}
