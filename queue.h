/* * * * * * *
 * Module for creating and manipulating a queue
 *
 * created for COMP20007 Design of Algorithms - Assignment 1, 2017
 * adopted from Matt Faruggia's "list"" code.
 * by Axel Bachtiar (ID: 774994) <abachtiar@unimelb.edu.au>
 */

#include <stdbool.h>

typedef struct queue Queue;

//create new queue and return pointer to it
Queue *new_queue();

//destroy the queue and free its memory
void free_queue(Queue *queue);

//add a new element to the queue
void insert_queue(Queue *queue, int data);

// remove and return the first element of the queue
int queue_remove_start(Queue *queue);

// return last data in the queue
int last_queue(Queue *queue);

//returns the number of elements in the queue
int queue_size(Queue *queue);

//returns the first element in the queue
int first_queue(Queue *queue);
