/*
Class:   CS 452 - Operating Systems
Project: P2 (aka P6) Bounded Buffer
Author:  Mark Muench
*/

#ifndef LAB_H
#define LAB_H
#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif


  /**
   * @brief opaque type definition for a queue
   */
  typedef struct queue
  {
    int capacity;  // Capacity of queue
    int currSize;  // Current Size
    bool shutdown; // Flag to shutdown. If flag is set, only consumers can access queue.
    int** array;   // Array of pointers to data stored in the queue
    int head;      // int used to access head of items in queue
    int tail;      // int used to access tail of items in queue

    // TODO: **Gonna try to do with with global mutex in lab.c first**
    // pthread_mutex_t lock; // Mutex used to maintain synchronization during enqueue, dequeue
  } *queue_t;

  /**
   * @brief Initialize a new queue
   *
   * @param capacity the maximum capacity of the queue
   * @return A fully initialized queue
   */
  queue_t queue_init(int capacity);

  /**
   * @brief Frees all memory and related data signals all waiting threads.
   *
   * @param q a queue to free
   */
  void queue_destroy(queue_t q);

  /**
   * @brief Adds an element to the back of the queue
   *
   * @param q the queue
   * @param data the data to add
   */
  void enqueue(queue_t q, void *data);

  /**
   * @brief Removes the first element in the queue.
   *
   * @param q the queue
   */
  void *dequeue(queue_t q);

  /**
   * @brief Set the shutdown flag in the queue so all threads can
   * complete and exit properly
   *
   * @param q The queue
   */
  void queue_shutdown(queue_t q);

  /**
   * @brief Returns true is the queue is empty
   *
   * @param q the queue
   */
  bool is_empty(queue_t q);

  /**
   * @brief
   *
   * @param q The queue
   */
  bool is_shutdown(queue_t q);

  /*
   * @brief Prints queue contents
   * @param q The queue
   */
  void print_queue(queue_t q);

#ifdef __cplusplus
} // extern "C"
#endif

#endif