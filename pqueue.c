#include <stdio.h>
#include <stdlib.h>
#include "PriorityQueue.h"
#include "run.h"

//declare the head Node of the Queue and set it to null
struct Event* head = NULL;

//insert into the Queue by giving the element and it's priority as the parameters
//declare two temp Nodes, temp1 and temp2
//allocate memory to temp1 and set it's data and priority to be the same as the element to be inserted
//if the Queue is empty or if the priority of the element to be inserted is higher, add temp1 before the head and set it as the head
//if the Queue is not empty and the priority of the new element is lower than the head's, then traverse through the Queue until the correct position for its priority is found
void insert(struct Event* newEvent)
{
    int newElement;
    int eventPriority;
	struct Event* temp1;
	struct Event* temp2;

	temp1 = (struct Event*)malloc(sizeof(struct Event));

	temp1->type = newElement;
	temp1->timeStamp = eventPriority;

	//if the Queue is empty of if the element that is being inserted has a higher priority
	if (isEmpty() || eventPriority < head->timeStamp)
	{
		temp1->next = head;
		head = temp1;
	}

	else {
		temp2 = head;

		while (temp2->next != NULL && temp2->next->timeStamp <= eventPriority)
		{
			temp2 = temp2->next;
		}

		temp1->next = temp2->next;
		temp2->next = temp1;
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
int delete()
{
	struct Event* temp;
	int event;

	if (isEmpty())
	{
		return 0;
	}

	else 
	{
		temp = head;
		event = temp->type;
		head = head->next;
		free(temp);
	}

	printf("%s %d %s", "Deleted:", event, "\n");
	return event;
}

//check to see whether a Queue is empty or not by returning 1 if it is and 0 if it isn't
int isEmpty()
{
	if (head == NULL)
		return 1;
	else
		return 0;
}

//to print the Queue, first check whether it's empty. If it isn't, then traverse through the Queue and print out each
//Node's data and priority in the Queue
void printQueue() {
	struct Event* temp;
	temp = head;

	if (isEmpty())
	{
		return;
	}

	else {
		while (temp != NULL)
		{
			printf("%s %d %s %d", "Data:", temp->type, "Priority:",temp->timeStamp);
			printf("\n");
			temp = temp->next;
		}
	}
}

