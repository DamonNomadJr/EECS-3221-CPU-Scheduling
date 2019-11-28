#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

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
    int rear;
    vProcess * process;
} circularQueue;

static vProcess nullProcess = {-1, -1, -1};


/** Queue Related Operations */
int isFull(circularQueue * queue, int size){
    if( queue->rear == size-1) {
        // It's full
        return 1;
    } else {
        // It's not full yet
        return 0;
    }
}

int isEmpty(circularQueue * queue){
    if(queue->rear == -1) { 
        // It's empty
        return 1;
    } else {
        // It contains some element
        return 0;
    }
}

int enQueue(circularQueue * queue, vProcess process, int size){
    if (isFull(queue, size)){
        // Couldn't add the element
        return 0;
    } else {
        queue->rear = queue->rear + 1;
        queue->process[queue->rear] = process;
        // Added the element
        return 1;
    }
}

int deQueue(circularQueue *queue, int id, int size){
    vProcess returnItem;
    if(isEmpty(queue)) {
        // Queue was empty
        return 0;
    } else {
        for (int i = 0; i < size; i = i + 1){
            if (queue->process[i].id == id){
                // Found the element to remove
                if (i == queue->rear){
                    queue->rear = queue->rear - 1;
                    queue->process[i] = nullProcess;
                } else {
                    // Move everything after i to left
                    for(int j = i; j < size; j = j + 1) {
                        vProcess temp = queue->process[j+1];
                        queue->process[j] = temp;
                    }
                    queue->process[queue->rear] = nullProcess;
                    queue->rear --;
                }
                // Remove successful
                return 1;
            }
        }
        // Didn't find id
        return -1;
    } 
}

/** Process Creation Related Operations */
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

/** Printing Scheduler Operations */
void printList(vProcess * list, char * pName){
    int size = (int) sizeof(list) / sizeof(list[0]);
    for(int i = 0; i < SIZE; i = i + 1){
        printf("%s [Process id: %d, Execution Time: %d, Arival Time: %d]\t", pName, list[i].id, list[i].runTime, list[i].arival);
        if ((i+1) % 2 == 0 || i == (SIZE - 1)){
            printf("\n");
        }
    }
    printf("----------------\n");
}

void printReadyQueue(circularQueue * queue, char * pName){
    if (queue->rear == -1){
        printf("%s: Empty!\n", pName);
    } else {
        for(int i = 0; i < queue->rear+1; i = i + 1){
            printf("%s: [Process id: %d, Execution Time: %d, Arival Time: %d]\t", pName, queue->process[i].id, queue->process[i].runTime, queue->process[i].arival);
            if ((i+1) % 2 == 0 || i == queue->rear){
                printf("\n");
            }
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
    // List of jobs
    vProcess * sortedList = malloc(sizeof(vProcess) * SIZE);

    // Ready queue
    circularQueue readyList = {-1, (malloc(sizeof(vProcess) * RSIZE))};
    // Job queue
    circularQueue jobList = {-1 , (malloc(sizeof(vProcess) * SIZE))};

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
    printf("List of Processes to be queued:\n");
    printList(sortedList, "[LTS] Process");

    for(int i = 0; i < 8; i++){
        printf(".");
        sleep(1);
        if (i == 7) printf("\n");
    }

    //Time initial to 0
    //Each itteration of while loop incriments the time by 1
    int time = 0;
    int pCount = 0;
    int condition = 1;

    do {
        system("@cls||clear");
        printf("Time elapsed: %d\t Processes arrived: %d\t Jobs Stored: %d \n\n", time, pCount - 1, jobList.rear);
        while (!isFull(&readyList, RSIZE) && !isEmpty(&jobList)){
            int state_0 = enQueue(&readyList, jobList.process[0], RSIZE);
            if (state_0 != 1){
                printf("[Failed] Could not add process to read queue.\n\n");
                exit(EXIT_FAILURE);
            }
            else {
                int state_0_1 = deQueue(&jobList, jobList.process[0].id, SIZE);
                if (state_0 != 1){
                    printf("[Failed] Could not remove a process from job queue.\n\n");
                    exit(EXIT_FAILURE);
                }
            }
        }

        while (!isFull(&jobList, SIZE) && sortedList[pCount].arival == time){
            int state_1 = enQueue(&jobList, sortedList[pCount], SIZE);
            if (state_1 != 1){
                printf("[Failed] Could not add process.\n\n");
                exit(EXIT_FAILURE);
            } else {
                pCount ++;
            }
        }
        
        printReadyQueue(&jobList, "[LTS] Job Queue");
        printReadyQueue(&readyList, "[LTS] Ready Queue");

        for(int i = 0; i < (readyList.rear + 1); i++){
            readyList.process[i].runTime--;
            if (readyList.process[i].runTime <= 0){
                int state_2 = deQueue(&readyList, readyList.process[i].id, RSIZE);
                if (state_2 != 1){
                printf("[Failed] Could not remove process.\n\n");
                exit(EXIT_FAILURE);
                }
            }
        }
        // increase time
        time ++;
        sleep(1);
        if (isEmpty(&jobList) && isEmpty(&readyList) && time > 100){
            condition  = 0;
        }
    } while (condition);
}

void main(){
    vProcess * list = createProcesses();
    pthread_t thread1, thread2;

    printf("\nValidating\n");
    for (int i = 0; i < SIZE; i = i + 1)
    {
        if (list[i].id == i && list[i].runTime < 31 && list[i].runTime > 0){
            printf(".");
        } else {
        printf("\nError: Unexpected Values!\n id: %d \truntime:%d \tExpected: %d\n", list[i].id, list[i].runTime, i);
            exit(EXIT_FAILURE);
        }
    }
    printf("\nAll Good! \n\n");

    FCFS(list);
}