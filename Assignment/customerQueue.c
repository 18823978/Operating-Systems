#include "customerQueue.h"

/*
Jaron Rose 18823978
Queue c file to queue and dequeue customers in a linked list
*/

/*Create queue allocation*/
c_queue* head = NULL;
c_queue* tail = NULL;
int total;
int currentSize;

/*
Queue(ADD) customers into linked list
*/
Customer* enqueue(Customer* customerInfo)
{
    int val;
    c_queue* newCustomer = (c_queue*)malloc(sizeof(c_queue));

    /*Assign data to new node*/
    newCustomer->customer = customerInfo;

    val = isEmpty();
    if(val == 1)
    {
        head = newCustomer;
        head->previous = NULL;
        tail = newCustomer;
        tail->next = NULL;
    }
    else
    {
        /*If linked list is not empty, go to end*/
        while(tail->next != NULL)
        {
            /*last node is temp*/
            tail = tail->next;
        }
        tail->next = newCustomer;
        newCustomer->previous = tail;
        tail = newCustomer;
        tail->next = NULL;
    }
    total++;
    currentSize++;
    return tail->customer;
}

/*
Dequeue(REMOVE) customers from linked list
*/
Customer* dequeue()
{
    Customer* nodeValue = NULL;
    int val;
    val = isEmpty();
    if(val == 1)
    {
        printf("Queue is empty");
    }
    else
    {
        nodeValue = head->customer;
        head = head->next;
    }
    currentSize--;
    return nodeValue;
}

/*
Check if the queue is empty
*/
int isEmpty()
{
    int empty = FALSE;
    if(head == NULL)
    {
        empty = TRUE;
    }
    return empty;
}

/*
Retrieve first in queue customer
*/
Customer* peekFirst()
{
    Customer* nodeValue = NULL;
    int val;
    val = isEmpty();
    if(val == 1)
    {
        printf("First node is empty");
    }
    else
    {
        nodeValue = head->customer;
    }
    return nodeValue;
}

/*
Retrieve customer that is last in queue
*/
Customer* peekLast()
{
    Customer* nodeValue = NULL;
    int val;
    val = isEmpty();
    if(val == 1)
    {
        printf("First node is empty");
    }
    else
    {
        nodeValue = tail->customer;
    }
    return nodeValue;
}

/*
Free the queue array
*/
void freeQueue()
{
    c_queue* temp;
    while(head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

/*
Display all customers in the queue
*/
void displayList() 
{
    while (head->next != NULL) 
    {
        printf("Customer ID: %d\nCustomer Service Type: %c \n", head->customer->customerID, head->customer->serviceType);

        head = head->next;
    }
    if (head == NULL)
    {
        printf("list is empty\n");
    }
}

/*
Retrieve total customers that have been in queue
*/
int getTotal()
{
    return total;
}

/*
Retrieve current number of customers in queue
*/
int getCurrentSize()
{
    return currentSize;
}