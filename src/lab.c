/*
Class:   CS 452 - Operating Systems
Project: P2 (aka P6) Bounded Buffer
Author:  Mark Muench
*/

#include "lab.h"
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>

// Global vars
int tempInt;
int* retVal;

// Functions
queue_t queue_init(int capacity)
{
    queue_t queue;

    // Initialize queue struct vals
    queue->capacity = capacity;
    queue->currSize = 0;
    queue->shutdown = false;
    queue->head = 0;
    queue->tail = 0;

    // Malloc array for pointers (Note: this is a pointer array,
    //                          each idx will point to itm stored)
    queue->array = (int **)malloc(capacity * sizeof(int *));

    return queue;
}

void queue_destroy(queue_t q)
{
    // Check if array is NULL. If !NULL, free memory inside
    if (q->array != NULL)
    {
        for (int i = 0; i < q->currSize; i++)
        {
            // Free items in the array
            free(q->array[i]);
        }
        // Nullify the pointer (good practice)
        q->array = NULL;
    }
}

void enqueue(queue_t q, void *data)
{
    // Check if data is NULL --> Fail
    if (data == NULL){
        fprintf(stderr, "Data being placed in queue is NULL\n");
        exit(-1);
    }

    // Check if at MAX CAPACITY
    if (q->currSize == q->capacity){
        /*
        So uh... do I need to have whatever process is doing this wait 
        until the queue is decrimented?

        Pensive -_-
        */

       // TODO -- REMOVE ME
       printf("Queue is full. Please remove items from queue.\n");
       return;
    }

    q->currSize++; // Incremement number of items in queue
}

void *dequeue(queue_t q)
{
    // Return NULL if queue is empty
    if (q->currSize == 0)
    {
        return NULL; // TODO: Throw error message if empty? Or return nothing?
    }
 
    // Grab value at head
    tempInt = q->head;
    retVal = q->array[tempInt];
    tempInt++;

    // Update head
    q->head = tempInt;

    q->currSize--;           
    return retVal; // Return item at address
}

void queue_shutdown(queue_t q)
{
    q->shutdown = true;
}

bool is_empty(queue_t q)
{
    if (q->currSize == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool is_shutdown(queue_t q)
{
    return q->shutdown;
}
