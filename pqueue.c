// written by Eva Snyder

#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"

struct Node *HEAD = NULL;
struct Node *TAIL = NULL;
int SIZE = 0;

/**
*  Method to add a new node to the queue which takes in a value and a priority
**/
int add (int new_value, int new_priority) {
	printf("Adding element: %d\n", new_priority);
	// create a new node with the size of a Node
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	// save the value as passed to the value in the node
	newNode -> value = new_value;
	newNode -> priority = new_priority;
	// save the next within the node as null i.e it's now the last node
	newNode -> next = NULL;

	// if we have no other nodes in our list currently i.e head is null
	if (HEAD == NULL) {
		// new node is the head
		HEAD = newNode;
		// new node is also the tail
		TAIL = newNode;

		SIZE = SIZE + 1;
		return 1;
	} else if(HEAD -> priority < new_priority) {
		// if our new priority should be the first in the list
		// i.e if the head priority is less than our new one
		newNode -> next = HEAD;
		HEAD = newNode;
		SIZE = SIZE + 1;
		return 1;
	} else if(TAIL -> priority > new_priority) {
			TAIL -> next = newNode;
			TAIL = newNode;
			SIZE = SIZE + 1;
	}
	else {
		struct Node* newHead = HEAD;
		if(newHead -> next == NULL) {
			HEAD -> next = newNode;
			TAIL = newNode;
		}
		else {
			// if the next node's priority is less than the priority you're inserting you want to insert in before that node
			while(newHead -> next -> priority > new_priority) {
				newHead = newHead -> next;
			}
				// insert here
				newNode -> next = newHead -> next;
				newHead -> next = newNode;
				SIZE = SIZE + 1;
		}
		return 1;
	}
	return 0;
}

/**
* Method to remove a node in the queue based off of it's priority
**/
int removeNode (int new_priority) {
	printf("Removing Element: %d\n", new_priority);

	if(!contains(new_priority)) {
		printf("Your queue does not contain that priority.\n Cannot be removed.\n");
		return 0;
	}

	// if the list is empty
	// i.e head is equal to null
	if(HEAD == NULL) {
		// there's nothing to do because it's already empty so woohoo
		printf("The queue is already empty\n");
		return 0;
	} else if (HEAD -> priority == new_priority) {
		// if we're removing the head
		HEAD = HEAD -> next;
		SIZE = SIZE - 1;
	} else {
		struct Node* newHead = HEAD;
		// if we're not looking at the tail
		if(newHead -> next != TAIL) {
			while(newHead -> next -> priority != new_priority) {
				newHead = newHead -> next;
			}
			// if the next node is the one we want to remove
			if(newHead -> next -> priority == new_priority) {
				struct Node* nodeToRemove = newHead -> next;
				newHead -> next = nodeToRemove -> next;
				free(nodeToRemove);
			}
		} else {
			// if we're removing the tail element
			newHead -> next = NULL;
			TAIL = newHead;
		}
		return 1;
	}

	return 0;
}

/**
* A method which checks to see if the passed priority is in the queue
**/
int contains(int new_priority) {
	struct Node* newHead = HEAD;
	while(newHead != NULL) {
		if(newHead -> priority == new_priority) {
			return 1;
		} else {
			newHead = newHead -> next;
		}
	}
	return 0;
}

/**
* Method which returns the priority of the head node
**/
int peek() {
	return HEAD -> priority;
}

/**
* Method that returns the size of the queue
**/
int size() {
	return SIZE;
}

/**
* Method that prints out the queue
**/
void printQueue() {
	struct Node* newHead = HEAD;
	printf("Your Priority Queue: ");
	while(newHead != NULL) {
		printf(" %d", newHead -> priority);
		newHead = newHead -> next;
	}
	printf("\n");
}

/**
* Method to check if the queue is empty
**/
int isEmpty() {
	if(HEAD == NULL && TAIL == NULL) {
		return 1;
	} else {
		return 0;
	}
}

/**
* Method to clear the queue completely
**/
void clearQueue() {
	struct Node* temp = HEAD;
	while(temp != NULL) {
		struct Node* nodeToRemove = temp;
		temp = temp -> next;
		free(nodeToRemove);
	}
	HEAD = NULL;
	TAIL = NULL;
	SIZE = 0;
}
