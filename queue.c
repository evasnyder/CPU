#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

//queue pointers
struct Node *QUEUE_HEAD = NULL;
struct Node *QUEUE_TAIL = NULL;
int QUEUE_SIZE = 0;



/**
* Method to add a node to the queue at the back of it.
**/
void enqueue (int new_value) {
	printf("Enqueueing element: %d\n", new_value);
	// create a new node with the size of a Node
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

	// save the next within the node as null i.e it's now the last node
	newNode -> next = NULL;

	// save the value as passed to the value in the node
	newNode -> value = new_value;

	// if we have no other nodes in our list currently i.e head is null
	if(QUEUE_HEAD == NULL) {
		// new node is the head
		QUEUE_HEAD = newNode;
		// new node is also the tail
		QUEUE_TAIL = newNode;

		QUEUE_SIZE = QUEUE_SIZE + 1;

		return;
	}

	// tail now points to the new value node
	QUEUE_TAIL -> next = newNode;

	// tail is now the new node
	QUEUE_TAIL = newNode;

	QUEUE_SIZE = QUEUE_SIZE + 1;
}

/**
* Method to remove the head node from the queue
**/
void dequeue() {
	printf("Dequeueing element");
	// save the value of the head before the dequeue begins
	// going to print the value of the currentHead after you remove it from the list
	struct Node* headToBeRemoved = QUEUE_HEAD;

	// if the list is empty
	// i.e head is equal to null
	if(QUEUE_HEAD == NULL) {
		// there's nothing to do because it's already empty so woohoo
		printf("The queue is already empty\n");
	} else if (QUEUE_HEAD == QUEUE_TAIL) {
		// if there is one node in the queue i.e head == tail
		// take away the head and tail
		QUEUE_HEAD = NULL;
		QUEUE_TAIL = NULL;
		QUEUE_SIZE = QUEUE_SIZE - 1;
	} else {
		// head is now whatever the original head is pointing to
		QUEUE_HEAD = QUEUE_HEAD -> next;
		printf("The dequeued node value is: %d\n", headToBeRemoved -> value);
		QUEUE_SIZE = QUEUE_SIZE - 1;
	}

	// remove the current head from the queue
	free(headToBeRemoved);
}

/**
* Method which returns the value of the head node
**/
int peek() {
	return QUEUE_HEAD -> value;
}

/**
* Returns the size of the queue
**/
int size() {
	return QUEUE_SIZE;
}

/**
* Method that prints out the queue
**/
void printQueue() {
	struct Node* newHead = QUEUE_HEAD;
	printf("Your Queue: ");
	while(newHead != NULL) {
		printf(" %d", newHead -> value);
		newHead = newHead -> next;
	}
	printf("\n");
}

/**
* Method to check and see if the queue is empty
**/
int isEmpty() {
	if(QUEUE_HEAD == NULL && QUEUE_TAIL == NULL) {
		return 1;
	} else {
		return 0;
	}
}

/**
* Method to clear the queue completely
**/
void clearQueue() {
	struct Node* temp = QUEUE_HEAD;
	while(temp != NULL) {
		struct Node* nodeToRemove = temp;
		temp = temp -> next;
		free(nodeToRemove);
	}
	QUEUE_HEAD = NULL;
	QUEUE_TAIL = NULL;
	QUEUE_SIZE = 0;
}
