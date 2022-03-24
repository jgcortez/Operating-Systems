#include <stdlib.h>
#include "threads.h"

typedef struct Semaphore
{
    int value;
    Queue* semQ;
} Sem;

Sem W_sem;
Sem R_sem;

// Sem* InitSem(int n);
void InitSem(Sem* s, int n);
void P(Sem* s);
void V(Sem* s);

// Sem* InitSem(int n)
// {
//     Sem* s = (Sem*) malloc(sizeof(Sem));
//     s->value = n;
//     s->semQ = InitQueue();
//     return s;
// }

void InitSem(Sem* s, int n){
    s->value = n;
    s->semQ = InitQueue();
}

void P(Sem* s)
{   
    //int i = 0;
    //printf("pval: %d\n", s->value);
    while (1) {
        //printf("sValP: %d\n", s->value);
        if(s->value <= 0) {
            AddQueue(s->semQ, DelQueue(ReadyQ));
            //printf("Gets Put On semQ\n");
            if (ReadyQ->head == NULL) exit(0);
            swapcontext(&(s->semQ->tail->context), &(ReadyQ->head->context));
        }
        else {
            s->value--;
            //printf("decremented to: %d\n", s->value);
            return;
        }
        //printf("loop num: %d", ++i);
    }
    //printf("loop exit");
}

void V(Sem* s)
{
    //printf("sValV: %d\n", s->value);
    //s->value++;
    if (s->semQ->head != NULL) {
        //printf("enteredIf\n");
        TCB_t* deleted = DelQueue(s->semQ);
        AddQueue(ReadyQ, deleted);
        //printf("Gets Put On ReadyQ\n");
        //AddQueue(ReadyQ, DelQueue(s->semQ));
        //printf("addedQ\n");
    }
    s->value++;
    //printf("bfYield\n");
    //yield();
    //printf("yielded\n");
}