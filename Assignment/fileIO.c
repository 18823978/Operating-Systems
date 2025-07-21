#include "fileIO.h"

/*
* Jaron Rose 18823978
* File input, reads given file and writes (APPENDS) to given file
*/
int count = 0;

void* open(void* fileName)
{
    /*Variable declarations*/
    FILE* file;
    Customer* customer;
    int done;
    int currentLine;
    int keepReading;
    char* line;
    char* temp;

    /*Current line in the file*/
    currentLine = 0;
    done = FALSE;
    keepReading = TRUE;

    /*Memory allocation*/
    line = (char*)malloc(sizeof(char*));
    /*Open the file*/
    file = fopen((char*)fileName, "r");
    customer = (Customer*)malloc(sizeof(Customer));
    do
    {
        /*File is empty or doesnt exist*/
        if(file == NULL)
        {
            perror("Error opening file: ");
            done = TRUE;
        }
        else
        {
            if(ferror(file))
            {
                perror("Error reading file: ");
                done = TRUE;
            }
            else
            { 
                currentLine = 0;
                do
                {
                    /*Get first line*/
                    fgets(line, sizeof(line), file);
                    if(feof(file))
                    {
                        keepReading = FALSE;
                    }
                    /*Continue last place in the file*/
                    else if(currentLine == count)
                    {
                        /*Tokenise to assign values to customer*/
                        temp = strtok(line, " ");
                        customer->customerID = atoi(temp);
                        temp = strtok(NULL, " ");
                        customer->serviceType = *(char*)temp;
                        customer->arrivalTime = systemTime();
                        keepReading = FALSE;
                    }
                    currentLine++;
                } 
                while (keepReading);
                count++;
                done = TRUE;
            }  
        }
    } 
    while (!done);
    free(line);
    if(file != NULL)
    {
        /*Close file*/
        fclose(file);
    }
    return (void*)customer;
}

/*Log customer details*/
void customerLog(Customer* customer)
{
    FILE* file;
    char* fileName;

    fileName = "r_log.txt";
    /*Append to file*/
    file = fopen(fileName, "a");

    if(file == NULL)
    {
        perror("Error opening file: ");
        free(customer);
    }
    else
    {
        if(ferror(file))
        {
            perror("Error reading file: ");
            free(customer);
        }
        else
        {
            fprintf(file, "-------------------------------------------------\n");
            fprintf(file, "Customer %d: %c\n", customer->customerID, customer->serviceType);
            fprintf(file, "Arrival Time: %s", asctime(customer->arrivalTime));
            fprintf(file, "-------------------------------------------------\n");
        }
    }
    /*Close file*/
    fclose(file); 
}

/*Teller response logging*/
void tellerResponseLog(Customer* customer)
{
    FILE* file;
    char* fileName;

    fileName = "r_log.txt";
    /*Append to file*/
    file = fopen(fileName, "a");

    if(file == NULL)
    {
        perror("Error opening file: ");
        free(customer);
    }
    else
    {
        if(ferror(file))
        {
            perror("Error reading file: ");
            free(customer);
        }
        else
        {
            fprintf(file, "-------------------------------------------------\n");
            fprintf(file, "Teller: %d\n", customer->tellerID);
            fprintf(file, "Customer: %d\n", customer->customerID);
            fprintf(file, "Arrival Time: %s", asctime(customer->arrivalTime));
            fprintf(file, "Response Time: %s", asctime(customer->responseTime));
            fprintf(file, "-------------------------------------------------\n");
        }
    }
    /*Close file*/
    fclose(file);
}

/*Teller will log when finished serving customer*/
void tellerCompletionLog(Customer* customer)
{
    FILE* file;
    char* fileName;

    fileName = "r_log.txt";
    /*Append to file*/
    file = fopen(fileName, "a");

    if(file == NULL)
    {
        perror("Error opening file: ");
        free(customer);
    }
    else
    {
        if(ferror(file))
        {
            perror("Error reading file: ");
            free(customer);
        }
        else
        {
            fprintf(file, "-------------------------------------------------\n");
            fprintf(file, "Teller: %d\n", customer->tellerID);
            fprintf(file, "Customer: %d\n", customer->customerID);
            fprintf(file, "Arrival Time: %s", asctime(customer->arrivalTime));
            fprintf(file, "Completion Time: %s", asctime(customer->completionTime));
            fprintf(file, "-------------------------------------------------\n");
        }
    }
    /*Close file*/
    fclose(file);
}

/*When teller terminates, teller will log information*/
void tellerTerminationLog(Customer* customer, Teller* teller)
{
    FILE* file;
    char* fileName;

    fileName = "r_log.txt";
    /*Append to file*/
    file = fopen(fileName, "a");

    if(file == NULL)
    {
        perror("Error opening file: ");
        free(customer);
    }
    else
    {
        if(ferror(file))
        {
            perror("Error reading file: ");
            free(customer);
        }
        else
        {
            fprintf(file, "-------------------------------------------------\n");
            fprintf(file, "Termination: %d\n", customer->tellerID);
            fprintf(file, "#Served Customers: %d\n", teller->servedCustomers);
            fprintf(file, "Start Time: %s", asctime(teller->startTime));
            fprintf(file, "Termination Time: %s", asctime(teller->terminationTime));
            fprintf(file, "-------------------------------------------------\n");
        }
    }
    /*Close file*/
    fclose(file);
}

/*When no more customers are in queue, last teller will log all teller statistics*/
void* tellerStatisticLog(void* teller)
{
    FILE* file;
    char* fileName;
    int total;
    Teller* tellers;

    tellers = (Teller*)teller;

    fileName = "r_log.txt";
    /*Append to file*/
    file = fopen(fileName, "a");

    if(file == NULL)
    {
        perror("Error opening file: ");
    }
    else
    {
        if(ferror(file))
        {
            perror("Error reading file: ");
        }
        else
        {
            total = getTotal();
            fprintf(file, "-------------------------------------------------\n");
            fprintf(file, "Teller Statistics\n");
            fprintf(file, "Teller 1 served: %d\n", tellers[0].servedCustomers);
            fprintf(file, "Teller 2 served: %d\n", tellers[1].servedCustomers);
            fprintf(file, "Teller 3 served: %d\n", tellers[2].servedCustomers);
            fprintf(file, "Teller 4 served: %d\n", tellers[3].servedCustomers);
            fprintf(file, "Total number of customers: %d\n", total);
            fprintf(file, "-------------------------------------------------\n");
        }
    }
    /*Close file*/
    fclose(file);

    return 0;
}