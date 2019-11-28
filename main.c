#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

//Choose how many processes to create
#define SIZE 100
//Choose ready queue size
#define RSIZE 5

typedef struct{
    int id;
    int runTime;
    int arival;
} vProcess;

typedef struct{
    int front;
    int rear;
    vProcess * process;
} circularQueue;

int isFull(circularQueue * queue){
    printf("Is Full %d, %d\n", queue->front, queue->rear);
    if( (queue->front == queue->rear + 1) || (queue->front == 0 && queue->rear == RSIZE-1)) {
        // It's full
        return 1;
    } else {
        // It's not full yet
        return 0;
    }
}

int isEmpty(circularQueue * queue){
    if(queue->front == -1) { 
        // It's empty
        return 1;
    } else {
        // It contains some element
        return 0;
    }
}

int enQueue(circularQueue * queue, vProcess process){
    if (isFull(queue)){
        // Couldn't add the element
        return 0;
    } else {
        if (queue->front == -1) {
            queue->front = 0;
        }
        queue->rear = (queue->rear + 1) % RSIZE;
        queue->process[queue->rear] = process;
        // Added the element
        return 1;
    }
}
int deQueue(circularQueue *queue, int id)
{
    vProcess returnItem;
    if(isEmpty(queue)) {
        // Queue was empty
        return 0;
    } else {
        for (int i = 0; i < RSIZE; i = i + 1){
            printf("Check ID: %d, id: %d\n",queue->process[i].id, id);
            if (queue->process[i].id == id){
                // Found the element to remove
                if (i == queue->front && i == queue->rear){
                    queue->front = -1;
                    queue->rear = -1;
                }else if (i < RSIZE - 1){
                    queue->front = i + 1;
                } else {
                    queue->front = 0;
                }
                // Remove successful
                return 1;
            }
        }
        // Didn't find id
        return -1;
    } 
}
vProcess instantiateProcess(int number){
    int randomTime = rand() % 30 + 1;
    int randomArival = rand() % 50 + 1;
    vProcess temp = { number, randomTime, randomArival };
    return temp;
}

vProcess * createProcesses(){
    printf("Constructing %d vPs\n", SIZE);
    vProcess * list = malloc(sizeof(vProcess) * SIZE);
    for (int i = 0; i < SIZE;  i = i + 1)
    {
        list[i] = instantiateProcess(i);
        printf("Consructing vP #%d, runtime: %d\n", list[i].id, list[i].runTime);
    }

    return list;
}

void printProcessQueue(vProcess * list, char * pName){
    int size = (int) sizeof(list) / sizeof(list[0]);
    for(int i = 0; i < SIZE; i = i + 1){
        printf("[%s] Job Queue: [Process id: %d, Execution Time: %d, Arival Time: %d]\t", pName, list[i].id, list[i].runTime, list[i].arival);
        if ((i+1) % 2 == 0 || i == (SIZE - 1)){
            printf("\n");
        }
    }
    printf("----------------\n");
}

/**
 * First Come First Serve
 * --
 * [processList]: (vProcess) unsorted process list
 * --
 * An implementation of first come first serve application. Given a process list
 * we copy the content of the list in to a secondary local list. Then we attempt
 * to sort the list by the arrival time.
 */
void FCFS(vProcess * processList){
    // Job queue
    vProcess * sortedList = malloc(sizeof(vProcess) * SIZE);
    // Ready queue
    circularQueue readyList = { -1, -1, (malloc(sizeof(vProcess) * RSIZE))};
    // Copy the content of processList to sortedList to avoid memory leakage!
    for(int i = 0; i < SIZE; i = i + 1){
        sortedList[i] = processList[i];
    }

    // Sort the priority by arrival time using insertion sort algorithem. O(n^2)
    int j;
    vProcess key;
    for (int i = 1; i < SIZE; i = i + 1) { 
        key = sortedList[i]; 
        j = i - 1; 
  
        /* Move elements of arr[0..i-1], that are 
          greater than key, to one position ahead 
          of their current position */
        while (j >= 0 && sortedList[j].arival > key.arival) { 
            sortedList[j + 1] = sortedList[j]; 
            j = j - 1; 
        } 
        sortedList[j + 1] = key;
    }
    // Printing out the jobQueue
    printProcessQueue(sortedList, "LTS");

    int x = enQueue(&readyList, sortedList[0]);
    printf("Operation enque status: %d, id: %d\n", x, sortedList[0].id);
    printf("Front %d, Rear %d\n", readyList.front, readyList.rear);
    printf("iD: %d\n", readyList.process[0]);

    x = enQueue(&readyList, sortedList[1]);
    printf("Operation enque status: %d, id: %d\n", x, sortedList[1].id);
    printf("Front %d, Rear %d\n", readyList.front, readyList.rear);
    printf("iD: %d\n", readyList.process[1]);

    x = enQueue(&readyList, sortedList[2]);
    printf("Operation enque status: %d, id: %d\n", x, sortedList[2].id);
    printf("Front %d, Rear %d\n", readyList.front, readyList.rear);
    printf("iD: %d\n", readyList.process[2]);

    x = enQueue(&readyList, sortedList[3]);
    printf("Operation enque status: %d, id: %d\n", x, sortedList[3].id);
    printf("Front %d, Rear %d\n", readyList.front, readyList.rear);
    printf("iD: %d\n", readyList.process[3]);

    x = enQueue(&readyList, sortedList[4]);
    printf("Operation enque status: %d, id: %d\n", x, sortedList[4].id);
    printf("Front %d, Rear %d\n", readyList.front, readyList.rear);
    printf("iD: %d\n", readyList.process[4]);
    //LIMIT
    x = enQueue(&readyList, sortedList[5]);
    printf("Operation enque status: %d, id: %d\n", x, sortedList[5].id);
    printf("Front %d, Rear %d\n", readyList.front, readyList.rear);
    printf("iD: %d\n", readyList.process[5]);

    x = deQueue(&readyList, 52);
    printf("Operation dequeue status: %d, id: %d\n", x, 52);
    printf("Front %d, Rear %d\n", readyList.front, readyList.rear);
}

void main(){
    vProcess * list = createProcesses();
    pthread_t thread1, thread2;

    printf("Validating\n");
    for (int i = 0; i < SIZE; i = i + 1)
    {
        if (list[i].id == i && list[i].runTime < 31 && list[i].runTime > 0){
            printf(".");
        } else {
        printf("\nError: Unexpected Values!\n id: %d \truntime:%d \tExpected: %d\n", list[i].id, list[i].runTime, i);
            exit(EXIT_FAILURE);
        }
    }
    printf("\n");

    FCFS(list);
}