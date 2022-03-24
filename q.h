#include <stdio.h>
#include <stdlib.h>
#include "tcb.h"

typedef struct Queue
{
    TCB_t* head;
    TCB_t* tail;
} Queue;

Queue* InitQueue();
void AddQueue(Queue* queue, TCB_t* newTCB);
TCB_t* DelQueue(Queue* queue);
void RotateQueue(Queue* queue);


Queue* InitQueue(){
    Queue* newQueue;
    newQueue = (Queue*)malloc(sizeof(Queue*));
    return newQueue;
}

void AddQueue(Queue* queue, TCB_t* newTCB){
    if (queue->head == NULL) {
        queue->head = newTCB;
        queue->tail = newTCB;
        newTCB->next = queue->head;
        newTCB->prev = queue->tail;
    }
    else {
        newTCB->prev = queue->tail;
        newTCB->next = queue->head;
        queue->tail->next = newTCB;
        queue->tail = newTCB;
        queue->head->prev = newTCB;
    }
}

TCB_t* DelQueue(Queue* queue)
{
    if(queue->head != NULL) {
        TCB_t* deleteTCB = queue->head;

        if (queue->head == queue->tail){
        queue->head = NULL;
        queue->tail = NULL;
        }
        else {
            queue->head = queue->head->next;
            queue->head->prev = queue->tail;
            queue->tail->next = queue->head;
        }

        return deleteTCB;   // Returns pointer to deleted item
    }
}

void RotateQueue(Queue* queue)
{
    if(queue->head != NULL){
        TCB_t* deletedTCB = DelQueue(queue);
        AddQueue(queue, deletedTCB);
    }
}