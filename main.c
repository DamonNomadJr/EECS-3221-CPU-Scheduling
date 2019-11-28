#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
    int id;
    int runTime;
    int arival;
} vProcess;

vProcess instantiateProcess(int number){
    int randomTime = rand() % 30 + 1;
    int randomArival = rand() % 50 + 1;
    vProcess temp = { number, randomTime, randomArival };
    return temp;
}

vProcess * createProcesses(){
    printf("Constructing 100 vPs\n");
    vProcess * list = malloc(sizeof(vProcess) * 100);
    for (int i = 0; i < 100;  i = i + 1)
    {
        list[i] = instantiateProcess(i);
        printf("Consructing vP #%d, runtime: %d\n", list[i].id, list[i].runTime);
    }

    return list;
}

void FirstComeFirstServe(vProcess * processList){
    vProcess * sortedList = malloc(sizeof(vProcess) * 100);
    
    printf("ProcessList 1: %d:%d:%d\n", processList[1].id, processList[1].runTime, processList[1].arival);
    
}

void main(){
    vProcess * list = createProcesses();
    pthread_t thread1, thread2;

    printf("Validating\n");
    for (int i = 0; i < 100; i = i + 1)
    {
        if (list[i].id == i && list[i].runTime < 31 && list[i].runTime > 0){
            printf(".");
        } else {
        printf("\nError: Unexpected Values!\n id: %d \truntime:%d \tExpected: %d\n", list[i].id, list[i].runTime, i);
            exit(EXIT_FAILURE);
        }
    }
    printf("\n");

    FirstComeFirstServe(list);
}