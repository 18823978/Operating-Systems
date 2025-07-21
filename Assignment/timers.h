#ifndef TIMERS_H
#define TIMERS_H

/*
Jaron Rose 18823978
Get system local time
*/

#include <time.h>
#include <stdio.h>

struct tm* systemTime();

#define TRUE 1
#define FALSE !TRUE

#endif