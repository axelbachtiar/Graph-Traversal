/* * * * * * *
 * Module for creating and manipulating a stack
 *
 * created for COMP20007 Design of Algorithms - Assignment 1, 2017
 * adopted from Matt Faruggia's "list"" code.
 * by Axel Bachtiar (ID: 774994) <abachtiar@unimelb.edu.au>
 */

#include <stdbool.h>

typedef struct stack Stack;

//create new stack and return pointer to it
Stack *new_stack();

//destroy the stack and free its memory
void free_stack(Stack *stack);

//put a variable in the end of the stack
void stack_push(Stack *stack, int data);

//remove and return the last data n the stack
int stack_pop(Stack *stack);

// return the last element of the queue
int last_stack(Stack *stack);

//returns the number of elements in the stack
int stack_size(Stack *stack);
