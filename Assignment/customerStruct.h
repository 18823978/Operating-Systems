#ifndef CUSTOMERSTRUCT_H
#define CUSTOMERSTRUCT_H
/*
Jaron Rose 18823978
Customer Struct to store customer information
*/
typedef struct Customer
{
    int customerID;
    char serviceType;
    int tellerID;
    struct tm* arrivalTime;
    struct tm* responseTime;
    struct tm* completionTime;
}Customer;

#endif