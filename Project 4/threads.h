#include "q.h"
#include <stdio.h>

Queue* ReadyQ;

void start_thread(void (*function)(int), int threadID)
{
    int stackSize = 8192;
    void* stack = (void*)malloc(stackSize);
    TCB_t* tcb = (TCB_t*)malloc(sizeof(TCB_t));
    init_TCB(tcb, function, stack, stackSize, threadID);
    AddQueue(ReadyQ, tcb);
}

void run()
{
    ucontext_t parent;      // get a place to store the main context, for faking
    getcontext(&parent);    // magic sauce
    swapcontext(&parent, &(ReadyQ->head->context));      // start the first thread
}

void yield() // similar to run
{
    RotateQueue(ReadyQ); // rotate the run Q;
    swapcontext(&(ReadyQ->head->prev->context), &(ReadyQ->head->context)); // swap the context, from previous thread to the thread pointed to by RunQ
}

