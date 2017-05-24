/* * * * * * *
 * Module for traversing through graphs and outputing either a
 * depth-first search, breadth-first search, a detailed path
 * all paths or the shortest path.
 *
 * created for COMP20007 Design of Algorithms - Assignment 1, 2017
 * by Axel Bachtiar (ID: 774994) <abachtiar@unimelb.edu.au>
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "traverse.h"
#include "stack.h"
#include "queue.h"

// not actually infinity but it's the highest integer I can use
// (as far as I know)
#define INFINITY ~(1<<31)

typedef struct path Path;

// a path points to the distance of its minimum path, its
// actual path in words and the number of cities traversed
struct path {
	int min_distance, len_path;
	int min_path[100];
};

/* helper function prototypes */

// To make a new edge
Edge* new_edge(int u, int v, int w); 

// To make a temporary edge
Edge* make_temporary_edge(Graph* graph, int u); 

// Helper function to process and print part 4
void print_all_paths(Graph* graph, int current_id, int destination_id,
	bool visited[], int output[], int len_output); 

// Helper function for part 5.
void find_shortest_path(Graph* graph, Path* path, int current_id, 
	int destination_id, bool visited[], int output[], int len_output, 
	int distance, int last_distance); 

/* function definitions */

// print the result of a depth-first search algorithm given the graph
// and the starting city
void print_dfs(Graph *graph, int source_id) {
    Stack *stack = new_stack();
    int len_output = 1;

    bool visited[graph->maxn];
	memset(visited, 0, graph->maxn); // Initialising the visited indicator

	Edge* temporary_edge = make_temporary_edge(graph, source_id);

    // Inputing the initial location to the stack, print it and mark it as
    // visited
    stack_push(stack, source_id);
    visited[source_id] = true;
	printf("%s", graph->vertices[source_id]->label);
	printf("\n");

    // While the stack has elements
    while (stack_size(stack) > 0) {

			// Check if there are anymore valid edges in the vertex,
			// if there aren't anymore then we pop the most recent
			// element in the stack and process the element prior
	    	if (temporary_edge == NULL) {
				stack_pop(stack);
	    	}

	    	// Check if the edge is pointing to a visited vertex.
	    	// If yes, we go to the next edge
			else if (visited[temporary_edge->v] == true) {
	    		temporary_edge = temporary_edge->next_edge;
			}

		    // If we haven't visited the next vertex,then we add the vertex to
	    	// the stack and output and mark it as visited
			else {
				stack_push(stack, temporary_edge->v);
				temporary_edge = make_temporary_edge(graph, last_stack(stack));
				visited[last_stack(stack)] = true;
				printf("%s", graph->vertices[last_stack(stack)]->label);
				printf("\n");
				len_output++;

			}	
    }
    free_stack(stack);
}

// print the result of a breadth-first search algorithm given the graph
// and the starting city
void print_bfs(Graph *graph, int source_id) {
    Queue *queue = new_queue();
    int len_output = 1;

	bool visited[graph->maxn];
	memset(visited, 0, graph->maxn); // Initialising the "visited" indicator

    // Inputing the initial location to the queue, print it and mark it as
    // visited
    insert_queue(queue, source_id);
    visited[source_id] = true;
	printf("%s", graph->vertices[source_id]->label);
	printf("\n");

    // While the queue has elements.
    while (queue_size(queue) > 0) {
		// While the first element in the queue has existing edges.
		Edge* temporary_edge = make_temporary_edge(graph, first_queue(queue));
		while (temporary_edge != NULL) {

		    // Check if the vertex that the edge is pointing to
		    // has been visited. If yes, then we skip to the next edge.
			if (visited[temporary_edge->v] == true) {
				temporary_edge = temporary_edge->next_edge;
			}
		    // If we haven't visited the next vertex,then we add the vertex to
		    // end of the queue. Add to output and mark it as visited. Then we 
	    	// go to the next edge of the vertex.
		    else {
				insert_queue(queue, temporary_edge->v);
				printf("%s", graph->vertices[last_queue(queue)]->label);
				printf("\n");
				visited[last_queue(queue)] = true;
				len_output++;
				temporary_edge = temporary_edge->next_edge;
	    	}
		}
		// If there aren't anymore valid edges in the vertex, we remove the 
		// vertex from the queue and process the next vertex
		queue_remove_start(queue);

    }
    free_queue(queue);
}

// print a simple path with no repeated cities from source_id to
// destination_id using depth-first search traversal
void detailed_path(Graph *graph, int source_id, int destination_id){

	// Creating the stack to be used
	Stack *stack = new_stack();

	// To hold the output (assuming no city will have name lengths>100)
    char output_name[graph->maxn][100];
    int len_output = 1, i, output_distance[graph->maxn];

	// creating the visited indicator
    bool visited[graph->maxn];
	memset(visited, 0, graph->maxn); // Initialising the "visited" indicator

	// To create the temporary edge
	Edge* temporary_edge = make_temporary_edge(graph, source_id);

    // Inputing the initial location to the stack and output and mark it as
    // visited
    stack_push(stack, source_id);
    strcpy(output_name[0], graph->vertices[source_id]->label);
	output_distance[0] = 0;
    visited[source_id] = true;

	while (stack_size(stack) > 0) {

		// Check if there are anymore valid edges in the vertex,
		// or if we have already reached the destination.
		// if yes then we pop the most recent
		// element in the stack and process the element prior
	  	if (temporary_edge == NULL || visited[destination_id] == true) {
			stack_pop(stack);
	   	}

	   	// Check if the edge is pointing to a visited vertex.
	   	// If yes, we go to the next edge
		else if (visited[temporary_edge->v] == true) {
    		temporary_edge = temporary_edge->next_edge;
		}
	    // If we haven't visited the next vertex,then we add the vertex to
    	// the stack and output and mark it as visited
		else {
			output_distance[len_output] = output_distance[len_output-1] + 
				temporary_edge->weight;
			stack_push(stack, temporary_edge->v);
			temporary_edge = make_temporary_edge(graph, last_stack(stack));
			strcpy(output_name[len_output], 
				graph->vertices[last_stack(stack)]->label);
			visited[last_stack(stack)] = true;
			len_output++;
		}	
	}

    // Print the path in terms of the cities visited and the cumulative distance
    for (i = 0; i < len_output; i++) {
		printf("%s (%dkm)", output_name[i], output_distance[i]);
	    printf("\n");
	}
    free_stack(stack);
}

// Prints all paths from source_id to destination_id
void all_paths(Graph *graph, int source_id, int destination_id){
    int output[graph->maxn]; // Create the output array
    int len_output = 0; // Initialise output array

    bool visited[graph->maxn];
	memset(visited, 0, graph->maxn);	// Initialising the "visited" indicator 
										// to all false.

	// Call the helper function
	print_all_paths(graph, source_id, destination_id, visited, output, 
		len_output);

}

// Helper function to process and print part 4
void print_all_paths(Graph* graph, int current_id, int destination_id, 
		bool visited[], int output[], int len_output){

	int i;

	// create a temporary edge and make it equal to the first edge
	// of the graph in the current_id vertex
	Edge* temporary_edge = make_temporary_edge(graph, current_id);

	visited[current_id] = true; // Mark the current location as visited
	output[len_output] = current_id; // Append the current location to output
	len_output++; // increase the length of output

	// If the destination has been reached, print output
	if(visited[destination_id] == true){
		for(i = 0; i < len_output; i++){
			printf("%s", graph->vertices[output[i]]->label);
			if(i < len_output-1){
				printf(", ");
			}
			else{
				printf("\n");
			}
		}
	}

	// If the the current vertex is not the destination
	// recurse back to the function for every edge in the vertex
	// skip all vertex that has already been visited.
	else{
		// While the vertex still has edges
		while(temporary_edge != NULL){
			// if the edge is pointing to an unvisited vertex, recurse 
			// with that edge becoming the new source_id
			if(visited[temporary_edge->v] != true){
				print_all_paths(graph, temporary_edge->v, destination_id, 
					visited, output, len_output);
				temporary_edge = temporary_edge->next_edge;
			}
			// if the vertex has been visited, skip to the next edge
			else{
				temporary_edge = temporary_edge->next_edge;
			}
		}
	}
		
	// Once we have exhausted the vertex' edges, we remove it from current 
	// output and mark it as unvisited
	len_output--;
	visited[current_id] = false;
}

// Prints the shortest path from source_id to destination_id and that path's
// distance
void shortest_path(Graph *graph, int source_id, int destination_id){
	int current_path[graph->maxn]; // Create the output array
    int len_output = 0; // Initialise output array
	int last_distance = 0; // Store the distance from the previous city
	int distance = 0; // stores the current total distance
	int i;

	// creating the path struct to hold the information of the shortest
	// distance path
	Path* path = malloc(sizeof (*path));
	path->min_distance = INFINITY;
	path->len_path = 0;

    bool visited[graph->maxn];
	memset(visited, 0, graph->maxn);	// Initialising the "visited" indicator 
										// to all false

	// Call the helper function
	find_shortest_path(graph, path, source_id, destination_id, visited,
		current_path, len_output, distance, last_distance);

	// prints the shortest path and its distance
	for(i = 0; i < path->len_path; i++){
		printf("%s", graph->vertices[path->min_path[i]]->label);
		if(i < path->len_path-1){
			printf(", ");
		}
		else{
			printf(" (%dkm)\n", path->min_distance);
		}
	}

	free(path);
}

// Helper function for part 5.
void find_shortest_path(Graph* graph, Path* path, int current_id, 
		int destination_id, bool visited[], int current_path[], int len_output, 
		int distance, int last_distance){

	int i;
	
	// creating the temporary edge
	Edge* temporary_edge = make_temporary_edge(graph, current_id);

	visited[current_id] = true; // Mark the current location as visited
	current_path[len_output] = current_id;	// Append the current location to 
											// output
	len_output++;

	// If the destination has been reached, compare to any previous paths
	// saves the path with shorter total distance to the path structure
	if(visited[destination_id] == true){
		if(distance < path->min_distance){
			path->min_distance = distance;
			path->len_path = len_output;
			for(i = 0; i < len_output; i++){
				path->min_path[i] = current_path[i];
			}
		}
	}

	// If the the current vertex is not the destination
	// recurse back to the function for every edge in the vertex
	// skip all vertex that has already been visited.
	else{
		// While the vertex still has edges
		while(temporary_edge != NULL){
			// if the edge is pointing to an unvisited vertex, recurse with that
			// edge becoming the new source_id. Add the weight of the edge
			// before recursing and subtracting it after recursing.
			// Then process the next edge
			if(visited[temporary_edge->v] != true){
				distance += temporary_edge->weight;
				find_shortest_path(graph, path, temporary_edge->v, 
					destination_id, visited, current_path, len_output, distance,
					temporary_edge->weight);
				distance -= temporary_edge->weight;
				temporary_edge = temporary_edge->next_edge;
			}
			// if the vertex has been visited, skip to the next edge
			else{
				temporary_edge = temporary_edge->next_edge;
			}
		}
	}
		
	// Once we have exhausted the vertex' edges, we remove it from current path 
	// and mark it as unvisited.
	distance -= last_distance;
	len_output--;
	visited[current_id] = false;
}

// Function to make a an edge (without adding it to a vertex of a graph).
Edge* make_temporary_edge(Graph* graph, int u){
	int w = graph->vertices[u]->first_edge->weight;
	int v = graph->vertices[u]->first_edge->v;

	Edge* edge = new_edge(u, v, w);
	edge->next_edge = graph->vertices[u]->first_edge->next_edge;
	return edge;
}