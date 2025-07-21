#include "services.h"

/*
* Jaron Rose 18823978
* Functions for teller and customer to queue and dequeue
*/

int queueSize;
int customerArrival;
int withdrawalTime;
int depositTime;
int informationTime;

/*Initialise variables for sleep times*/
void services(int queueNum, int customerTimer, int w, int d, int i)
{
    queueSize = queueNum;
    customerArrival = customerTimer;
    withdrawalTime = w;
    depositTime = d;
    informationTime = i;
}

/*Enqueue customers to the queue*/
void* customer(void* fileName)
{
    Customer* customer;
    int i;
    for(i = 0; i < queueSize; i++)
    {
        /*Retrieve customer from file*/
        customer = open(fileName);

        /*Queue customer*/
        pthread_mutex_lock(&customerMutex);
        enqueue(customer); 
        pthread_mutex_unlock(&customerMutex);

        /*Log customer information*/
        pthread_mutex_lock(&logMutex);
        customerLog(customer);
        pthread_mutex_unlock(&logMutex);

        /*Wait for next customer to arrive*/
        sleep(customerArrival);
    }
    return 0;
}

/*Determines which service type to how long teller will take to serve customer*/
void getSleep(Customer* customer)
{
    if(customer->serviceType == 'w')
    {
        sleep(withdrawalTime);
    }
    else if(customer->serviceType == 'd')
    {
        sleep(depositTime);
    }
    else if(customer->serviceType == 'i')
    {
        sleep(informationTime);
    }
    else
    {
        /*Default*/
        sleep(2);
    }
}

/*Teller will retrieve customer from queue, and serve customer based on
sleep time, and then log all information*/
void* teller(void* teller)
{
    Customer* customer;
    Teller* custTeller;
    int val;

    /*Cast void* to teller*/
    custTeller = (Teller*) teller;
    val = isEmpty();
    if(val != 1)
    {
        /*Grab customer from the queue*/
        pthread_mutex_lock(&queueMutex);
        customer = dequeue();
        pthread_mutex_unlock(&queueMutex);

        /*Teller is serving the customer*/
        getSleep(customer);

        /*Get system time*/
        customer->responseTime = systemTime();
        customer->tellerID = custTeller->tellerID;

        /*Log information*/
        pthread_mutex_lock(&logMutex);
        tellerResponseLog(customer);
        pthread_mutex_unlock(&logMutex);

        getSleep(customer);

        /*Get system time*/
        customer->completionTime = systemTime();

        /*Log information*/
        pthread_mutex_lock(&logMutex);
        tellerCompletionLog(customer);
        pthread_mutex_unlock(&logMutex);

        /*Keep track of how many customers teller has served*/
        custTeller->servedCustomers += 1;
        
        getSleep(customer);
        
        /*Get system time*/
        custTeller->terminationTime = systemTime();

        /*Log information*/
        pthread_mutex_lock(&logMutex);
        tellerTerminationLog(customer, custTeller);
        pthread_mutex_unlock(&logMutex);    
    }
    
    return 0;
}