// Name: Josue Cortez

#include <stdio.h>
#include <stdlib.h>
#include "threads.h"

int globalCount = 0;

void testThread();

void main()
{
    int numOfThreads, numOfExecutions, i = 1;
    char comma;

    RunQ = InitQueue();

    scanf("%d%c%d", &numOfThreads, &comma, &numOfExecutions);
    // scanf("%d[^,],%d", &numOfThreads, &numOfExecutions);

    if(numOfThreads == 0) {
        printf("No Threads\n");
        return;
    }

    while(i <= numOfThreads) {
        start_thread(testThread, i, numOfExecutions);
        i++;
    }

    run();
}

void testThread(int threadID, int numOFExecutions)
{
    int count = 0;
    
    while(count < numOFExecutions){
        globalCount += threadID;
        count++;

        printf("\n This is %d th execution of thread %d with global var value %d \n", count, threadID, globalCount);
        
        yield();
    }

}
