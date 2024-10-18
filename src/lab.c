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

/* Global vars */
int tempInt;
int *retVal;
pthread_mutex_t mutex;
pthread_cond_t not_full;  // Condition variable to signal not full
pthread_cond_t not_empty; // Condition variable to signal not empty

/* Functions */
queue_t queue_init(int capacity)
{
    // Allocate memory for the queue
    queue_t queue = (queue_t)malloc(sizeof(struct queue));

    // Check if malloc succeeded
    if (queue == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for queue\n");
        return NULL;
    }

    // Initialize queue struct vals
    queue->capacity = capacity;
    queue->currSize = 0;
    queue->shutdown = false;
    queue->head = 0;
    queue->tail = 0;

    // Malloc array for pointers (Note: this is a pointer array,
    //                          each idx will point to itm stored)
    queue->array = (int **)malloc(capacity * sizeof(int *));

    // Initialize mutex for synchronization
    pthread_mutex_init(&mutex, NULL);

    return queue;
}

void queue_destroy(queue_t q)
{
    // Unlock mutex just in case...
    pthread_mutex_unlock(&mutex);

    // Check if array is NULL. If !NULL, free memory inside
    if (q->array != NULL)
    {
        for (int i = 0; i < q->capacity; i++)
        {
            // Free items in the array
            // if (q->array[i] != NULL){
            //     free(q->array[i]);
            // }
            // else {
                q->array[i] = NULL; // Will nullifying pointer work? Idk
            // }
        }
        // Nullify the pointer (good practice)
        q->array = NULL;
    }
    pthread_mutex_destroy(&mutex);
}

void enqueue(queue_t q, void *data)
{
    printf("Enqueue: %d\n", *(int *)data);

    // Lock mutex
    int result = pthread_mutex_lock(&mutex);

    if (result == 0)
    {
        printf("lock successful\n");
    }
    else
    {
        printf("failure\n");
    }
    // TODO: Check if mutex lock is actually working. Check for retval, maybe change parameter??

    // Check if data is NULL --> Fail
    if (data == NULL)
    {
        fprintf(stderr, "Data being placed in queue is NULL\n");
        exit(-1);
    }

    // Check if shutdown flagged --> Not allowed to add anything
    if (q->shutdown == true)
    {
        pthread_mutex_unlock(&mutex);
        return;
    }

    // Check if at MAX CAPACITY --> attempt to lock mutex
    while (q->currSize == q->capacity)
    {
        // Wait for the capacity to be reduced, try to lock if possible
        pthread_cond_wait(&not_full, &mutex);
    }

    // Check if head index is out of bounds.
    if (q->head == q->capacity)
    {
        q->head = 0;
    }
    q->array[q->head] = data; // Update pointer to referenced data
    q->head++;
    q->currSize++; // Incremement number of items in queue

    // Unlock mutex for critical section
    pthread_cond_signal(&not_empty);
    pthread_mutex_unlock(&mutex);
}

void *dequeue(queue_t q)
{
    // Lock mutex
    pthread_mutex_lock(&mutex);

    // Check if in shutdown and size is 0 -> Exit and return NULL
    if (q->shutdown && (q->currSize == 0))
    {
        pthread_mutex_unlock(&mutex);
        printf("Queue is being shutdown. Remaining Elements:\n");
        for (int i = 0; i < q->capacity; i++)
        {
            printf("[%d]%d\n", i, *q->array[i]);
        }
        return NULL;
    }

    // Wait till queue has an element in it
    while (q->currSize == 0)
    {
        pthread_cond_wait(&not_empty, &mutex);
    }

    // Check case for when your tail is outside bounds.
    if (q->tail == q->capacity)
    {
        q->tail = 0;
    }

    // Grab value at tail
    tempInt = q->tail;
    retVal = q->array[tempInt];

    // // Nullify the pointer in the array
    q->array[tempInt] = NULL;
    tempInt++;

    // Update head
    q->tail = tempInt;
    q->currSize--;

    // Unlock mutex
    pthread_cond_signal(&not_full);
    pthread_mutex_unlock(&mutex);

    printf("Dequeue: %d\n", *retVal);
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

void print_queue(queue_t q)
{
    if (q->capacity == 0)
    {
        printf("Queue is EMPTY.\n");
    }
    printf("Printing queue contents:\nCapacity:%d\nCurrSize:%d\n", q->capacity, q->currSize);
    for (int i = 0; i < q->currSize; i++)
    {
        printf("[%d]", q->tail);
        printf(" %d\n", *q->array[q->tail]); // TODO: Figure out how to dereference object
    }
}
