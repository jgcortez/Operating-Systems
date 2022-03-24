// Name: Josue Cortez

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sem.h"

//Sem mutex;
Sem W_Sem;
Sem R_Sem;
int* buff = NULL;
int readers, writers;

int rc = 0;
int wc = 0;
int rwc = 0;
int wwc = 0;
int i = 0;

void Writer(int writerID);
void Reader(int readerID);

void main()
{
    //int numOfThreads;
    int currentThreadID;
    char comma;

    ReadyQ = InitQueue();
    //printf("a\n");
    //scanf("%d%c%d", &numOfThreads, &comma, &numOfExecutions);
    scanf("%d%c%d", &readers, &comma, &writers);
    
    InitSem(&W_Sem, 0);
    InitSem(&R_Sem, 0);

    for(int j = 0; j < readers + writers; j++) {
        //printf("j: %d\n", j);
        scanf("%d", &currentThreadID);
        //printf("ID: %d\n", currentThreadID);
        if(currentThreadID > 0){
            //printf("Positive\n");
            start_thread(Reader, currentThreadID);
            //printf("Positive\n");
        }
        else if(currentThreadID <= 0){
            //printf("Negative\n");
            start_thread(Writer, currentThreadID);
            //printf("Negative\n");
        }
    }
    run();
}

void Writer(int writerID){
    // Writer Entry
    if (rc > 0 || wc > 0 || rwc > 0 || wwc > 0){
        wwc++;
        P(&W_Sem);
        
        wwc--;
    }
    //i++;
    wc++;
    i++;
    printf("\n This is the %d th writer writing value i = %d \n", -writerID, i);
    yield();

    // Writer Exit
    //printf("\n This is the %d th writer writing value i = %d for the first time \n", -writerID, i);
    wc--;
    if (rwc > 0) {
        for (int j = 0; j < rwc; j++){
            V(&R_Sem);
        }
    }
    else if (wwc > 0){
        V(&W_Sem);
    }
    printf("\n This is the %d th writer verifying value i = %d \n", -writerID, i);

    TCB_t* deleted = DelQueue(ReadyQ);

    if(ReadyQ->head != NULL){
        swapcontext(&(deleted->context), &(ReadyQ->head->context));
    }
}

void Reader(int readerID){
    // Reader Entry
    if (wwc > 0 || wc > 0){
        rwc++;
        P(&R_Sem);
        rwc--;
    }
    rc++;
    printf("\n This is the %d th reader reading value i = %d for the first time \n", readerID, i);
    yield();

    // Reader Exit
    //printf("\n This is the %d th reader reading value i = %d for the first time \n", readerID, i);
    rc--;
    if (rc == 0 && wwc > 0) {
        V(&W_Sem);
    }
    printf("\n This is the %d th reader reading value i = %d for the second time \n", readerID, i);

    TCB_t* deleted = DelQueue(ReadyQ);

    if(ReadyQ->head != NULL){
        swapcontext(&(deleted->context), &(ReadyQ->head->context));
    }
}