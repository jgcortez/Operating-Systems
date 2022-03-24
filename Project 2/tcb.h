#include <stdlib.h>
#include <string.h>
#include <ucontext.h>

typedef struct TCB_t  
{
    ucontext_t context; 
    struct TCB_t *prev;  
    struct TCB_t *next;  
} TCB_t;   

void init_TCB (TCB_t* tcb, void *function, void *stackP, int stack_size, int threadID, int numOFExecutions)
{
    memset(tcb, '\0', sizeof(TCB_t));
    getcontext(&tcb->context);
    tcb->context.uc_stack.ss_sp = stackP;
    tcb->context.uc_stack.ss_size = (size_t) stack_size;
    makecontext(&tcb->context, function, 2, threadID, numOFExecutions);
}
