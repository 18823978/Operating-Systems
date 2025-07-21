#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "fileIO.h"
#include "customerStruct.h"
#include "customerQueue.h"
#include "timers.h"
#include "tellerStruct.h"

/*
Jaron Rose 18823978
FILE IO to read and write to files
*/

#include "customerQueue.h"
#include "tellerStruct.h"

void* open(void* fileName);
void customerLog(Customer* customer);
void tellerResponseLog(Customer* customer);
void tellerCompletionLog(Customer* customer);
void tellerTerminationLog(Customer* customer, Teller* teller);
void* tellerStatisticLog(void* teller);

#define TRUE 1
#define FALSE !TRUE

#endif
