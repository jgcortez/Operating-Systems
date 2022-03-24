#include "q.h"
#include <stdio.h>

Queue* RunQ;

void start_thread(void (*function)(int, int), int threadID, int numOfExecutions)
{
    int stackSize = 8192;
    void* stack = (void*)malloc(stackSize);
    TCB_t* tcb = (TCB_t*)malloc(sizeof(TCB_t));
    init_TCB(tcb, function, stack, stackSize, threadID, numOfExecutions);
    AddQueue(RunQ, tcb);
}

void run()
{
    ucontext_t parent;      // get a place to store the main context, for faking
    getcontext(&parent);    // magic sauce
    swapcontext(&parent, &(RunQ->head->context));      // start the first thread
}

void yield() // similar to run
{
    RotateQueue(RunQ); // rotate the run Q;
    swapcontext(&(RunQ->head->prev->context), &(RunQ->head->context)); // swap the context, from previous thread to the thread pointed to by RunQ
}

