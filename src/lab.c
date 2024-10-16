/*
Class:   CS 452 - Operating Systems
Project: P2 (aka P6) Bounded Buffer
Author:  Mark Muench
*/

#include "lab.h"
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

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
    printf("%p\n", data);

    q->currSize++; // Incremement number of items in queue
}

void *dequeue(queue_t q)
{

    // Return if queue is empty
    if (q->currSize == 0)
    {
        return;
    }

    Node *retVal = &q->node; // Grab current node address
    q->node = *q->node.next; // Set currNode to nextNode
    q->currSize--;           // Decrement number of items in queue

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
