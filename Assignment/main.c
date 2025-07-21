#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "fileIO.h"
#include "customerQueue.h"
#include "customerStruct.h"
#include "tellerStruct.h"
#include "services.h"
#include "timers.h"
#include <unistd.h>

/*
* Jaron Rose 18823978
* Main function
*/

/*Number of teller threads can be changed to increase number of threads*/
#define TELLER_THREADS 4

/*Mutual Exclusion declarations*/
pthread_mutex_t queueMutex;
pthread_mutex_t customerMutex;
pthread_mutex_t logMutex;

/*Forward declarations*/
void customerThread(char* fileName);
void tellerThread();
void initialiseMutualExclusion();
void destroyMutualExclusion();

int main(int argc, char* argv[])
{
    /*
    Variable initialisation
    */
    int queueSize;
    int customerArrival;
    int withdrawal;
    int deposit;
    int information;
    char* fileName;

    fileName = "c_file.txt";
    /*
    If not enough commands given in the command line 
    */
    if(argc <= 5 || argc > 6)
    {
        printf("ERROR: invalid number of args entered.\n");
        printf("FORMAT: ./cq m(size of queue) t(time for customer arrival) t1 t2 t3(time for W D I service type).\n");
    }
    /*Commands must not be negative and queue size must be greater than 0 but smaller than 100*/
    else if(atoi(argv[1]) < 0 || atoi(argv[1]) > 100 || atoi(argv[2]) < 0 || atoi(argv[3]) < 0 || atoi(argv[4]) < 0 || atoi(argv[5]) < 0)
    {
        printf("ERROR: POSITIVE NUMBERS ONLY.\n");
        printf("FORMAT: ./cq m(0 < size of queue < 100) t(time for customer arrival) t1 t2 t3(time for W D I service type).\n");
    }
    else
    {
        /*Initialise mutual exclusions*/
        initialiseMutualExclusion();

        /*Take arguments and give to variables*/
        queueSize = atoi(argv[1]);
        customerArrival = atoi(argv[2]);
        withdrawal = atoi(argv[3]);
        deposit = atoi(argv[4]);
        information = atoi(argv[5]);

        /*Set sleep timers and queue size*/
        services(queueSize, customerArrival, withdrawal, deposit, information);
        sleep(customerArrival);

        /*Start and create threads*/
        customerThread(fileName);
        tellerThread();
        
        sleep(20);

        /*Free memory allocations*/
        destroyMutualExclusion();
        freeQueue();
        pthread_exit(0);
    }
    return 0;
}

/*This method will create a customer thread to run customer()*/
void customerThread(char* fileName)
{
    pthread_t id;
    
    pthread_create(&id, NULL, &customer, fileName);

    pthread_join(id, NULL);
}
/*This method will create 4 teller threads and 4 teller objects to run teller()*/
void tellerThread()
{
    pthread_t* id;
    Teller* tellers;
    int val;
    int i;

    /*Memory allocations*/
    id = (pthread_t*)malloc(sizeof(pthread_t) * TELLER_THREADS);
    tellers = (Teller*)malloc(sizeof(Teller) * TELLER_THREADS);
    for(i = 0; i < TELLER_THREADS; i++)
    {
        /*Default values*/
        tellers[i].tellerID = i + 1;
        tellers[i].servedCustomers = 0;
        tellers[i].startTime = systemTime();
    }

    val = isEmpty();
    while(val != 1)
    {
        /*If queue is empty while running, pause and wait for customers*/
        val = isEmpty();
        if(val == 1)
        {
            sleep(2);
        }
        /*4 Teller threads*/
        pthread_create(&id[0], NULL, &teller, &tellers[0]);
        pthread_join(id[0], NULL);
        
        pthread_create(&id[1], NULL, &teller, &tellers[1]);
        pthread_join(id[1], NULL);

        pthread_create(&id[2], NULL, &teller, &tellers[2]);
        pthread_join(id[2], NULL);

        pthread_create(&id[3], NULL, &teller, &tellers[3]);
        pthread_join(id[3], NULL);
    } 
    pthread_create(&id[3], NULL, &tellerStatisticLog, tellers);

    pthread_join(id[0], NULL);
    pthread_join(id[1], NULL);
    pthread_join(id[2], NULL);
    pthread_join(id[3], NULL);

    /*Free memory allocations*/
    free(tellers);
    free(id);

    pthread_exit(0);
}

/*Initialise mutexes and conditions*/
void initialiseMutualExclusion()
{
    pthread_mutex_init(&queueMutex, NULL);
    pthread_mutex_init(&logMutex, NULL);
    pthread_mutex_init(&sleepMutex, NULL);
    pthread_cond_init(&tellerCondition, NULL);
}

/*Destroy mutexes and conditions*/
void destroyMutualExclusion()
{
    pthread_mutex_destroy(&queueMutex);
    pthread_mutex_destroy(&logMutex);
    pthread_mutex_destroy(&sleepMutex);
    pthread_cond_destroy(&tellerCondition);
}