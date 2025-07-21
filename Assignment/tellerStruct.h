#ifndef TELLERSTRUCT_H
#define TELLERSTRUCT_H
/*
Jaron Rose 18823978
Struct to store teller information
*/
typedef struct Teller
{
    int tellerID;
    int servedCustomers;
    struct tm* startTime;
    struct tm* terminationTime;
}Teller;

#endif