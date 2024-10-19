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
    // print_queue(q);
    if (q->array != NULL)
    {
        for (int i = 0; i < q->capacity; i++)
        {
            // Set pointers in the queue to NULL
            q->array[i] = NULL;
        }

        // Free the array
        free(q->array);
    }
    pthread_mutex_destroy(&mutex);
}

void enqueue(queue_t q, void *data)
{
    // printf("Enqueue: %d\n", *(int *)data);

    // Lock mutex
    pthread_mutex_lock(&mutex);

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

    // Check if at MAX CAPACITY
    while (q->currSize == q->capacity)
    {
        pthread_cond_wait(&not_full, &mutex);
    }

    // Check if head index is out of bounds.
    if (q->head == q->capacity)
    {
        q->head = 0;
    }
    q->array[q->head] = data; // Update pointer to referenced data
    q->head++;
    q->currSize++; // Increment number of items in queue

    // Signal that the queue is not empty anymore
    pthread_cond_signal(&not_empty);
    pthread_mutex_unlock(&mutex);
}

void *dequeue(queue_t q)
{
    // Lock mutex
    pthread_mutex_lock(&mutex);

    // Somehow I have an off by 1 index error (hitting -1 for size ugh)
    if (q->currSize <= 0)
    {
        print_queue(q);
    }

    // Check if in shutdown and size is 0 -> Exit and return NULL
    if ((q->currSize == 0) && q->shutdown)
    {
        pthread_mutex_unlock(&mutex);
        return NULL;
    }

    // Wait till queue has an element in it
    while (q->currSize == 0 && !q->shutdown)
    {
        pthread_cond_wait(&not_empty, &mutex);
    }


    // // If shutdown is triggered after waking up, return NULL
    // if (q->shutdown)
    // {
    //     pthread_mutex_unlock(&mutex);
    //     // Check case for when your tail is outside bounds.
    //     if (q->tail == q->capacity)
    //     {
    //         q->tail = 0;
    //     }

    //     // Grab value at tail
    //     void *retVal = q->array[q->tail];
    //     q->array[q->tail] = NULL;
    //     q->tail++;
    //     q->currSize--;

    //     // Signal that the queue is not full anymore

    //     // printf("Dequeue: %d\n", *(int *)retVal);
    //     return retVal;
    // }

    // Check case for when your tail is outside bounds.
    if (q->tail == q->capacity)
    {
        q->tail = 0;
    }

    // Grab value at tail
    void *retVal = q->array[q->tail];
    q->array[q->tail] = NULL;
    q->tail++;
    q->currSize--;

    // Signal that the queue is not full anymore
    pthread_cond_signal(&not_full);
    pthread_mutex_unlock(&mutex);

    // printf("Dequeue: %d\n", *(int *)retVal);
    return retVal;
}

void queue_shutdown(queue_t q)
{
    // printf("shutdown called\n");
    // printf("\tcurrSize: %d\n", q->currSize);

    // Signal all threads to wake up
    q->shutdown = true;
    pthread_cond_broadcast(&not_empty);
    pthread_cond_broadcast(&not_full);
}

bool is_empty(queue_t q)
{
    print_queue(q);
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
        // Print location in queue
        printf("[%d]", i);
        if (q->array[i] != NULL)
        {
            // Print item, if exists
            printf(" %d\n", *q->array[i]);
        }
        else
        {
            // Print null if doesn't exist
            printf(" NULL\n");
        }
    }
}
