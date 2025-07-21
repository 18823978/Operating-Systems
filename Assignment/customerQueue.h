#ifndef CUSTOMERQUEUE_H
#define CUSTOMERQUEUE_H

#include "customerQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include "customerStruct.h"
/*
Jaron Rose 18823978
Customer Queue to add customers or remove customers from the queue
*/

#include "customerStruct.h"
#include "pthread.h"

pthread_mutex_t queueMutex;
pthread_mutex_t customerMutex;
pthread_mutex_t logMutex;
pthread_mutex_t sleepMutex;
pthread_cond_t tellerCondition;
pthread_cond_t tellerFinishCondition;

typedef struct c_queue
{
    Customer* customer;
    struct c_queue *next;
    struct c_queue *previous;
}c_queue;

Customer* enqueue(Customer* customerInfo);
Customer* dequeue();
int isEmpty();
Customer* peekFirst();
Customer* peekLast();
void displayList();
void freeQueue();
int getTotal();
int getCurrentSize();

#define TRUE 1
#define FALSE !TRUE

#endif