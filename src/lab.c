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

    // TODO: Do I need to malloc queue? -- Unsure.

    queue->capacity = capacity;
    queue->currSize = 0;
    queue->shutdown = false;

    // Malloc array based on new capacity.

    return queue;
}

void queue_destroy(queue_t q);

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

    return retVal;           // Return item at address
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
