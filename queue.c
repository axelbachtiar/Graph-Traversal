/* * * * * * *
 * Module for creating and manipulating a queue
 *
 * created for COMP20007 Design of Algorithms - Assignment 1, 2017
 * adopted from Matt Faruggia's "list"" code.
 * by Axel Bachtiar (ID: 774994) <abachtiar@unimelb.edu.au>
 */

#include <stdlib.h>
#include <assert.h>
#include "queue.h"

typedef struct node Node;

// a list node points to the next node in the list, and to some data
struct node {
	Node *next;
	int data;
};

// the queue points to its first and last nodes, and stores its size (num. nodes)
struct queue {
	Node *head;
	Node *tail;
	int size;
};

/* helper function prototypes */

// helper function to create a new node and return its address
Node *new_node_in_queue();

// helper function to clear memory of a node (does not free the node's data)
void free_node_in_queue(Node *node);

/* function definitions */

// create a new queue and return a pointer to it
Queue *new_queue(){
	Queue *queue = malloc(sizeof *queue);
	assert(queue);
	
	queue->head = NULL;
	queue->tail = NULL;
	queue->size = 0;

	return queue;
}

// helper function to create a new node and return its address
Node *new_node_in_queue() {
	Node *node = malloc(sizeof *node);
	assert(node);
	
	return node;
}  

// helper function to clear memory of a node
void free_node_in_queue(Node *node) {
	free(node);
}

//destroy the queue and free its memory
void free_queue(Queue *queue){
	assert(queue != NULL);
	// free each node
	Node *node = queue->head;
	Node *next;
	while (node) {
		next = node->next;
		free_node_in_queue(node);
		node = next;
	}
	// free the queue struct itself
	free(queue);
}

// add a new element to the queue
void insert_queue(Queue *queue, int data){
	assert(queue != NULL);
	
	// we'll need a new queue node to store this data
	Node *node = new_node_in_queue();
	node->data = data;
	node->next = NULL; // as the last node, there's no next node

	if(queue->size == 0) {
		// if the queue was empty, new node is now the first node
		queue->head = node;
	} else {
		// otherwise, it goes after the current last node
		queue->tail->next = node;
	}
	
	// place this new node at the end of the queue
	queue->tail = node;
	
	// and keep size updated too
	queue->size++;
}

// remove and return the first element of the queue
int queue_remove_start(Queue *queue) {
	assert(queue != NULL);
	assert(queue->size > 0);
	
	// we'll need to save the data to return it
	Node *start_node = queue->head;
	int data = start_node->data;
	
	// then replace the head with its next node (may be null)
	queue->head = queue->head->next;

	// if this was the last node in the queue, the tail also needs to be cleared
	if(queue->size == 1) {
		queue->tail = NULL;
	}

	// the queue is now one node smaller
	queue->size--;

	// and we're finished with the node holding this data
	free_node_in_queue(start_node);

	// done!
	return data;
} 

// return last data in the queue
int last_queue(Queue *queue){
	assert(queue != NULL);
	assert(queue->size > 0);
	
	Node *end_node = queue->tail;
	return end_node->data;
}                                                                                                                                                                                                                                                                                                                                                                                                                        

// returns the number of elements in the queue
int queue_size(Queue *queue){
	assert(queue != NULL);
	return queue->size;
}

// returns the first element of the queue
int first_queue(Queue *queue){
	assert(queue != NULL);
	Node *start_node = queue->head;
	return start_node->data;
}
