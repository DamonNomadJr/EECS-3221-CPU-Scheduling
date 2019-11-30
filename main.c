#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h> 

//GLOBAL DEFINITIONS
bool TEST = false;
int TIME = 0;
int PROCESS_COUNT = 0;
int CONSUMED_PROCESSES = 0;
//Default process size
int SIZE = 100;
//Default ready queue size
int RSIZE = 5;
//Default process max random time
int RAND_TIME = 30;
//Default process max random time
int RAND_ARRIVAL = 50;
//Sleep/wait time
int SLEEP_TIME = 5;


//Process Structure
typedef struct{
    int id;
    int runTime;
    int arrival;
} vProcess;


//Queue structure
typedef struct{
    int rear;
    int size;
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
        printf("\033[0;34m[TESTING]: %s\033[0m\n",text);
    }
}

/** Queue Related Operations */

/**
 * isFull | queue:[circularQueue *]
 * Takes a circularQueue type and decudes if the circular queue is full
 * or not.
 * !important: [1 ==  true] and [0 == false].
 */
bool isFull(circularQueue * queue){
    if( queue->rear == queue->size-1) {
        // It's full
        return true;
    } else {
        // It's not full yet
        return false;
    }
}

/**
 * isEmpty | queue:[circularQueue *]
 * Takes a circularQueue type and decudes if the circular queue is empty
 * or not.
 * !important: [1 ==  true] and [0 == false].
 */
bool isEmpty(circularQueue * queue){
    if(queue->rear == -1) { 
        // It's empty
        return true;
    } else {
        // It contains some element
        return false;
    }
}

/**
 * enQueue | queue:[circularQueue], process:[vProcess *]
 * Adds a virtual process type to a given queue.
 * !important: [1 ==  true] and [0 == false].
 */
bool enQueue(circularQueue * queue, vProcess process){
    if (isFull(queue)){
        // Couldn't add the element
        return false;
    } else {
        queue->rear = queue->rear + 1;
        queue->process[queue->rear] = process;
        // Added the element
        return true;
    }
}

/**
 * deQueue | queue:[circularQueue], process:[vProcess *]
 * Removes a virtual process type to a given queue.
 * !important: [1 ==  true] and [0 == false].
 */
bool deQueue(circularQueue *queue, int id, int size){
    vProcess returnItem;
    if(isEmpty(queue)) {
        // Queue was empty
        return false;
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
                return true;
            }
        }
        // Didn't find id
        return false;
    } 
}

/**
 * instantiateProcess | number:[int]
 * Creates and returns a virtual process object.
 */
vProcess instantiateProcess(int number){
    int randomTime = rand() % RAND_TIME + 1;
    int randomArrival = rand() % RAND_ARRIVAL + 1;
    vProcess temp = { number, randomTime, randomArrival };
    return temp;
}

/**
 * createProcesses
 * Instantiates a number of processes depending on user input, and
 * retuns a pointer to a list of processes.
 */
vProcess * createProcesses(){
    vProcess * list = malloc(sizeof(vProcess) * SIZE);
    for (int i = 0; i < SIZE;  i = i + 1)
    {
        list[i] = instantiateProcess(i);
    }

    return list;
}

/**
 * validateProcessesCreation | list:[vProcess *]
 * Validates creation of a process to be of ascending order by ID, and
 * all pointers exist.
 */
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

/**
 * printList | list:[vProcess *], text [char *]
 * Prints the given list on the screen with given pre-text.
 */
void printList(vProcess * list, char * text){
    if (TEST) {
        int size = (int) sizeof(list) / sizeof(list[0]);
        for(int i = 0; i < SIZE; i = i + 1){
            printf("%s [Process id: %02d, Execution Time: %02d, Arrival Time: %02d]\t", text, list[i].id, list[i].runTime, list[i].arrival);
            if ((i+1) % 2 == 0 || i == (SIZE - 1)){
                printf("\n");
            }
        }
        printf("----------------\n");
    }
}

/**
 * printQueue | queue:[circularQueue *], text [char *]
 * Prints the given queue on the screen with given pre-text.
 */
void printQueue(circularQueue * queue, char * text){
    if (queue->rear == -1){
        printf("%s: Empty!\n", text);
    } else {
        for(int i = 0; i < queue->rear+1; i = i + 1){
            printf("%s: [Process id: %02d, Execution Time: %02d, Arrival Time: %02d]\t", text, queue->process[i].id, queue->process[i].runTime, queue->process[i].arrival);
            if ((i+1) % 2 == 0 || i == queue->rear){
                printf("\n");
            }
        }
    }
    printf("----------------\n");
}

/**
 * FCFS | list:[void *]
 * First Come First Serve
 * Long term scheduler where incriments TIME by 1 every time. It also decides
 * which process is arriving (a silly implementation to mimic the behaviour 
 * of an active OS). Processes are put into globalJobQueue when their arrival 
 * time eques the time.
 * It is also responsible of queueing the jobs to arrival queue depending on
 * their arruvak tune.
 */
void * FCFS(void * list){

    vProcess * sortedList = (struct vProcess *) list;
        
    //Critical Section
    pthread_mutex_lock(&lock);
    testMessage("[LTS] Locking mutext");

    if (!isEmpty(globalJobList) && !isFull(globalReadyList) && CONSUMED_PROCESSES < SIZE){
        
        int state_0 = enQueue(globalReadyList, globalJobList->process[0]);
        if (state_0 != 1){
            testMessage("[Failed]:[LTS] Could not add process to ready queue.");
            exit(EXIT_FAILURE);
        }
        else {
            int state_0_1 = deQueue(globalJobList, globalJobList->process[0].id, SIZE);
            if (state_0 != 1){
                testMessage("[Failed]:[LTS] Could not remove a process from job queue.");
                exit(EXIT_FAILURE);
            }
        }
    }

    //Rest of operation.
    while (!isFull(globalJobList) && sortedList[PROCESS_COUNT].arrival == TIME){
        int state_1 = enQueue(globalJobList, sortedList[PROCESS_COUNT]);
        if (state_1 != 1){
            testMessage("[Failed]:[LTS] Could not add process.");
            exit(EXIT_FAILURE);
        } else {
            PROCESS_COUNT ++;
        }
    }
    
    printQueue(globalJobList, "[LTS] Job Queue");
    printQueue(globalReadyList, "[LTS] Ready Queue");

    // increase time
    TIME ++;
    testMessage("[LTS] Unlocking mutext");
    pthread_mutex_unlock(&lock);
}

/**
 * SJF
 * Shortes Job First
 * Short term scheduler it consumes the items in the ready queue and reduce
 * their time and pushes it back if and only if their time is positive.
 */
void * SJF(){

    pthread_mutex_lock(&lock);
    testMessage("[STS] Locking mutext");

    if (!isEmpty(globalReadyList) && CONSUMED_PROCESSES < SIZE){
        vProcess tempProcess = globalReadyList->process[0];

        for(int i = 1; i < globalReadyList->rear + 1; i++){
            if (tempProcess.runTime > globalReadyList->process[i].runTime){
                tempProcess = globalReadyList->process[i];
            }
        }
        int stat_0 = deQueue(globalReadyList, tempProcess.id, RSIZE);
        if (stat_0 != 1){
            testMessage("[Failed]:[STS] Could not remove a process from ready queue.\n");
            exit(EXIT_FAILURE);
        } else {
            printf("[STS]: Consuming Process ID: %02d\tRuntime: %02d\n", tempProcess.id, tempProcess.runTime);
            printQueue(globalReadyList, "[STS]: Ready Queue");
        }

        tempProcess.runTime = tempProcess.runTime - 2;
        if (tempProcess.runTime <= 0){
            CONSUMED_PROCESSES ++ ;
        } else {
            int state_1 = enQueue(globalReadyList, tempProcess);
            if (state_1 != 1){
                testMessage("[Failed]:[STS] Could not add a process to ready queue.\n");
                exit(EXIT_FAILURE);
            } else {
                printf("[STS]: Added Process ID: %02d\tRuntime: %02d\tArrival: %02d\n", tempProcess.id, tempProcess.runTime, tempProcess.arrival);
                printQueue(globalReadyList, "[STS]: Ready Queue");
            }
        }
    }
    testMessage("[STS] Unlocks mutex");
    pthread_mutex_unlock(&lock);
}

int main(int argc, char **argv){
    
    if (argc > 1){
        for (int i = 1; i < argc; i++){
            if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")){
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
                printf("\t\tChange the # of processes to execute at a time. Default 5\n\n");
                printf("\t--time | -s [value in int]:\n");
                printf("\t\tSets random run time for a process to max of a given time. Defult 30\n\n");
                printf("\t--arrival | -a [value in int]:\n");
                printf("\t\tSets random arrival time for a process to max of a given time. Defult 50\n\n");
                printf("\t--wait | -w [value in int]:\n");
                printf("\t\tWait duration before execution of processes. Defult 10\n\n");
                exit(EXIT_SUCCESS);
            }
        }
        for (int i = 1; i < argc; i++){
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
            else if(!strcmp(argv[i], "--time") || !strcmp(argv[i], "-s")){
                if (argv[i+1] != NULL) {
                    printf("Random max time is set %s\n", argv[i+1]);
                    RAND_TIME = atoi(argv[i+1]);
                } else {
                    exit(EXIT_FAILURE);
                }
            }
            else if(!strcmp(argv[i], "--arrival") || !strcmp(argv[i], "-a")){
                if (argv[i+1] != NULL) {
                    printf("Random max arrival time to be set %s\n", argv[i+1]);
                    RAND_ARRIVAL = atoi(argv[i+1]);
                } else {
                    exit(EXIT_FAILURE);
                }
            }
            else if(!strcmp(argv[i], "--wait") || !strcmp(argv[i], "-w")){
                if (argv[i+1] != NULL) {
                    printf("Waiting %s sec before executing\n", argv[i+1]);
                    SLEEP_TIME = atoi(argv[i+1]);
                } else {
                    exit(EXIT_FAILURE);
                }
            }
            else if(!strcmp(argv[i], "--test") || !strcmp(argv[i], "-t")){
                TEST = true;
            }
        }
    }

    printf("Creating %d jobs and %d is Ready size\n", SIZE, RSIZE);
    vProcess * list = createProcesses();

    //Validating if processes were created by ID for SIZE
    validateProcessesCreation(list);
    
    printList(list, "[Proces]");
    // Sorting Process By Time

    int j;
    vProcess key;
    for (int i = 1; i < SIZE; i = i + 1) { 
        key = list[i]; 
        j = i - 1; 
        while (j >= 0 && list[j].arrival > key.arrival) { 
            list[j + 1] = list[j]; 
            j = j - 1; 
        } 
        list[j + 1] = key;
    }
    testMessage("Sorting is completed");

    printList(list, "[Sorted]");

    //Initializeing process holders

    circularQueue tempR = {-1, RSIZE, malloc(sizeof(vProcess ) * RSIZE)};
    globalReadyList = &tempR;

    circularQueue tempJ = {-1, SIZE, malloc(sizeof(vProcess ) * SIZE)};
    globalJobList = &tempJ;

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("Mutex init failed\n");
        exit(EXIT_FAILURE);
    }

    sleep(SLEEP_TIME);
    //Keep creating process stacks
    while(true) {
        pthread_create(&thread1, NULL, FCFS, list);
        pthread_create(&thread2, NULL, SJF, NULL);
        if(CONSUMED_PROCESSES == SIZE){
            // pthread_cancel(thread1);
            // pthread_cancel(thread2);
            pthread_mutex_destroy(&lock);
            printQueue(globalJobList, "JOB LIST:");
            printQueue(globalReadyList, "READY LIST:");
            printf("Execution of jobs successfull\n");
            exit(EXIT_SUCCESS);
        }
    }
}