#ifndef SERVICES_H
#define SERVICES_H

/*
Jaron Rose 18823978
Teller and customer methods, teller will grab customers from queue,
customers will join the queue
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include "fileIO.h"
#include "customerQueue.h"
#include "timers.h"
#include "tellerStruct.h"
#include<unistd.h>
#include "customerStruct.h"

void services(int queueNum, int customerTimer, int w, int d, int i);
void getSleep(Customer* customer);
void* customer(void* fileName);
void* teller(void* tellerNum);

#define TRUE 1
#define FALSE !TRUE

#endif