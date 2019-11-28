#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

int TEST = 0;

//Choose how many processes to create
int SIZE = 100;
//Choose ready queue size
int RSIZE = 5;

typedef struct{
    int id;
    int runTime;
    int arival;
} vProcess;

typedef struct{
    int rear;
    vProcess * process;
} circularQueue;

// Empty process def
static vProcess nullProcess = {-1, -1, -1};

//Global Job List
circularQueue * globalJobList;
circularQueue * globalReadyList;

//Thread info
pthread_t thread1, thread2;
pthread_mutex_t lock;

void testMessage(char * text){
    if (TEST){
        printf("\033[0;34m");
        printf("[TESTING]: %s\n",text);
        printf("\033[0m");
    }
}

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
    vProcess * list = malloc(sizeof(vProcess) * SIZE);
    for (int i = 0; i < SIZE;  i = i + 1)
    {
        list[i] = instantiateProcess(i);
    }

    return list;
}

//Validating if processes were created by ID for SIZE
void validateProcessesCreation(vProcess* list){
    
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
}

/** Printing Scheduler Operations */
void printList(vProcess * list, char * pName){
    if (TEST){
        printf("\033[0;34m");
        int size = (int) sizeof(list) / sizeof(list[0]);
        for(int i = 0; i < SIZE; i = i + 1){
            printf("%s [Process id: %02d, Execution Time: %02d, Arival Time: %02d]\t", pName, list[i].id, list[i].runTime, list[i].arival);
            if ((i+1) % 2 == 0 || i == (SIZE - 1)){
                printf("\n");
            }
        }
        printf("----------------\n");
        sleep(10);
        printf("\033[0m");
    }
}

void printQueue(circularQueue * queue, char * pName){
    if (queue->rear == -1){
        printf("%s: Empty!\n", pName);
    } else {
        for(int i = 0; i < queue->rear+1; i = i + 1){
            printf("%s: [Process id: %02d, Execution Time: %02d, Arival Time: %02d]\t", pName, queue->process[i].id, queue->process[i].runTime, queue->process[i].arival);
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
void * FCFS(void * list){
    pthread_mutex_lock(&lock); 
    // List of jobs
    vProcess * sortedList = (struct vProcess *) list;

    // Sort the priority by arrival time using insertion sort algorithem. O(n^2)
    int j;
    vProcess key;
    for (int i = 1; i < SIZE; i = i + 1) { 
        key = sortedList[i]; 
        j = i - 1; 
        while (j >= 0 && sortedList[j].arival > key.arival) { 
            sortedList[j + 1] = sortedList[j]; 
            j = j - 1; 
        } 
        sortedList[j + 1] = key;
    }

    printf("Sorting DONE\n");
    printList(list, "SORTED LIST");

    pthread_mutex_unlock(&lock);

    //Time initial to 0
    //Each itteration of while loop incriments the time by 1
    int time = 0;
    int pCount = 0;
    int condition = 1;

    do {
        system("@cls||clear");
        printf("Time elapsed: %03d\t Processes arrived: %02d\t Jobs Stored: %02d \n\n", time, pCount - 1, globalJobList->rear + 1);
        pthread_mutex_lock(&lock); 
        testMessage("LOCKING MUTEX");
        while (!isFull(globalReadyList, RSIZE) && !isEmpty(globalJobList)){
            int state_0 = enQueue(globalReadyList, globalJobList->process[0], RSIZE);
            if (state_0 != 1){
                printf("[Failed] Could not add process to read queue.\n\n");
                exit(EXIT_FAILURE);
            }
            else {
                int state_0_1 = deQueue(globalJobList, globalJobList->process[0].id, SIZE);
                if (state_0 != 1){
                    printf("[Failed] Could not remove a process from job queue.\n\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
        testMessage("UNLOCKING MUTEX");
        pthread_mutex_unlock(&lock); 

        while (!isFull(globalJobList, SIZE) && sortedList[pCount].arival == time){
            int state_1 = enQueue(globalJobList, sortedList[pCount], SIZE);
            if (state_1 != 1){
                printf("[Failed] Could not add process.\n\n");
                exit(EXIT_FAILURE);
            } else {
                pCount ++;
            }
        }
        
        printQueue(globalJobList, "[LTS] Job Queue");
        printQueue(globalReadyList, "[LTS] Ready Queue");

        // increase time
        time ++;
        sleep(1);
        if (isEmpty(globalJobList) && isEmpty(globalReadyList) && time > 100){
            condition  = 0;
        }
    } while (condition);
}

void * SJF(){
    do {
        
    } while (1);
}

int main(int argc, char **argv){
    
    if (argc > 1){
        if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")){
            printf("CPU Scheduling design by Mehrzad B.\n");
            printf("For more info please visit: https://github.com/DamonNomadJr/EECS3221-CPU-Scheduling\n");
            printf("Arguments:\n");
            printf("\t--help | -h:\n");
            printf("\t\tOpens help\n\n");
            printf("\t--jobs | -j [value in int]:\n");
            printf("\t\tChange the number of jobs to be processed. Default 100\n\n");
            printf("\t--ready | -r [value in int]:\n");
            printf("\t\tChange the # of processes to execute at a time. Default 5\n\n");
            printf("\t--test | -t:\n");
            printf("\t\tRuns with test messages\n\n");
            return 0;
        }
        for (int i = 1; i < argc; i++){
            printf("Consumed %s\n", argv[i]);
            if(!strcmp(argv[i], "--ready") || !strcmp(argv[i], "-r")){
                if (argv[i+1] != NULL) {
                    printf("Ready to be set %s\n", argv[i+1]);
                    RSIZE = atoi(argv[i+1]);
                } else {
                    exit(EXIT_FAILURE);
                }
            }
            else if(!strcmp(argv[i], "--jobs") || !strcmp(argv[i], "-j")){
                if (argv[i+1] != NULL) {
                    printf("Jobs to be set %s\n", argv[i+1]);
                    SIZE = atoi(argv[i+1]);
                } else {
                    exit(EXIT_FAILURE);
                }
            }
            else if(!strcmp(argv[i], "--test") || !strcmp(argv[i], "-t")){
                TEST = 1;
            }
        }
    }

    printf("Creating %d jobs and %d is Ready size\n", SIZE, RSIZE);
    vProcess * list = createProcesses();

    //Validating if processes were created by ID for SIZE
    validateProcessesCreation(list);
    circularQueue tempR = {-1, malloc(sizeof(vProcess ) * RSIZE)};
    globalReadyList = &tempR;
    circularQueue tempJ = {-1, malloc(sizeof(vProcess ) * SIZE)};
    globalJobList = &tempJ;

    pthread_create(&thread1, NULL, FCFS, list);
    pthread_join(thread1, NULL);
    // pthread_create(&tid, NULL, FCFS, (void *)list);
    // pthread_join(tid, NULL);
    // int err = pthread_create(&thread1, NULL, FCFS, (void*) list);
}