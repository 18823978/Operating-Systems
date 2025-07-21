#include "timers.h"

/*
Jaron Rose 18823978
Method to retrieve system local time and date
*/

struct tm* systemTime()
{
    time_t rawTime;
    struct tm* timeInfo;

    time(&rawTime);
    timeInfo = localtime(&rawTime);

    return timeInfo;
}