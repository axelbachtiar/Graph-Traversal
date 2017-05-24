/* * * * * * *
 * Module for creating and manipulating a stack
 *
 * created for COMP20007 Design of Algorithms - Assignment 1, 2017
 * adopted from Matt Faruggia's "list"" code.
 * by Axel Bachtiar (ID: 774994) <abachtiar@unimelb.edu.au>
 */

#include "stack.h"
#include <stdlib.h>
#include <assert.h>

typedef struct node Node;

// a list node points to the next node in the list, and to some data
struct node {
	Node *next;
	int data;
};

// the stack points to its first and last nodes, and stores its size (num. nodes)
struct stack {
	Node *head;
	Node *tail;
	int size;
};

// helper function to create a new node and return its address
Node *new_node_stack();

// helper function to clear memory of a node (does not free the node's data)
void free_node_stack(Node *node);

// create a new stack and return a pointer to it
Stack *new_stack(){
	Stack *stack = malloc(sizeof *stack);
	assert(stack);
	
	stack->head = NULL;
	stack->tail = NULL;
	stack->size = 0;

	return stack;
}

// destroy a queue and its memory
void free_stack(Stack *stack){
	assert(stack != NULL);
	// free each node
	Node *node = stack->head;
	Node *next;
	while (node) {
		next = node->next;
		free_node_stack(node);
		node = next;
	}
	// free the stack struct itself
	free(stack);
}

// helper function to create a new node and return its address
Node *new_node_stack() {
	Node *node = malloc(sizeof *node);
	assert(node);
	
	return node;
}

// helper function to clear memory of a node
void free_node_stack(Node *node) {
	free(node);
}

// put a variable in the end of the stack
void stack_push(Stack *stack, int data){
	assert(stack != NULL);
	
	// we'll need a new stack node to store this data
	Node *node = new_node_stack();
	node->data = data;
	node->next = NULL; // as the last node, there's no next node

	if(stack->size == 0) {
		// if the stack was empty, new node is now the first node
		stack->head = node;
	} else {
		// otherwise, it goes after the current last node
		stack->tail->next = node;
	}
	
	// place this new node at the end of the stack
	stack->tail = node;
	
	// and keep size updated too
	stack->size++;
}

// remove and return the first data n the stack
int stack_pop(Stack *stack){
	assert(stack != NULL);
	assert(stack->size > 0);
	
	// we'll need to save the data to return it
	Node *end_node = stack->tail;
	int data = end_node->data;
	
	// then replace the tail with the second-last node (may be null)
	// (to find this replacement, we'll need to walk the stack --- the O(n) bit
	Node *node = stack->head;
	Node *prev = NULL;
	while (node->next) {
		prev = node;
		node = node->next;
	}
	stack->tail = prev;
	
	if(stack->size == 1) {
		// if we're removing the last node, the head also needs clearing
		stack->head = NULL;
	} else {
		// otherwise, the second-last node needs to drop the removed last node
		prev->next = NULL;
	}

	// the stack just got one element shorter
	stack->size--;

	// we're finished with the stack node holding this data
	free_node_stack(end_node);

	// done!
	return data;
}

// return the last element of the queue
int last_stack(Stack *stack){
	assert(stack != NULL);
	assert(stack->size > 0);
	
	Node *end_node = stack->tail;
	return end_node->data;
}
	
// returns the number of elements in the stack
int stack_size(Stack *stack){
	assert(stack != NULL);
	return stack->size;
}