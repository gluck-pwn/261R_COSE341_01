#include "queue.h"
#include <stdio.h>

void clear_queue(Queue *q){
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

void reset_scheduler_queues(){
    clear_queue(&ready_queue);
    clear_queue(&waiting_queue);
}

int queue_is_empty(Queue *q){
    return q->size == 0;
}

int queue_is_full(Queue *q){
    return q->size == MAX_QUEUE_SIZE;
}

void push_process(Queue *q, Process *p){
    if (queue_is_full(q)){
        printf("Queue is full\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->processes[q->rear] = p;
    q->size++;
}

Process *pop_process(Queue *q){
    if (queue_is_empty(q)){
        return NULL;
    }
    Process *p = q->processes[q->front];
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    q->size--;
    return p;
}

void take_process_out(Queue *q, Process *p){
    if (queue_is_empty(q)){
        return;
    }
    
    int i, j;
    for (i = 0; i < q->size; i++){
        int idx = (q->front + i) % MAX_QUEUE_SIZE;
        if (q->processes[idx] == p){
            for (j = i; j < q->size - 1; j++){
                int curr = (q->front + j) % MAX_QUEUE_SIZE;
                int next = (q->front + j + 1) % MAX_QUEUE_SIZE;
                q->processes[curr] = q->processes[next];
            }
            q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
            q->size--;
            return;
        }
    }
}

Process *pick_shortest_remaining_job(Queue *q){
    if (queue_is_empty(q)){
        return NULL;
    }
    
    Process *shortest = q->processes[q->front];
    int shortest_idx = q->front;
    
    for (int i = 1; i < q->size; i++){
        int idx = (q->front + i) % MAX_QUEUE_SIZE;
        if (q->processes[idx]->remaining_time < shortest->remaining_time){
            shortest = q->processes[idx];
            shortest_idx = idx;
        }
    }
    
    for (int i = shortest_idx; i < q->size - 1; i++){
        int curr = (q->front + i) % MAX_QUEUE_SIZE;
        int next = (q->front + i + 1) % MAX_QUEUE_SIZE;
        q->processes[curr] = q->processes[next];
    }
    q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
    q->size--;
    
    return shortest;
}

Process *pick_highest_priority_job(Queue *q){
    if (queue_is_empty(q)){
        return NULL;
    }
    
    Process *highest = q->processes[q->front];
    int highest_idx = q->front;
    
    for (int i = 1; i < q->size; i++){
        int idx = (q->front + i) % MAX_QUEUE_SIZE;
        if (q->processes[idx]->priority < highest->priority){
            highest = q->processes[idx];
            highest_idx = idx;
        }
    }
    
    for (int i = highest_idx; i < q->size - 1; i++){
        int curr = (q->front + i) % MAX_QUEUE_SIZE;
        int next = (q->front + i + 1) % MAX_QUEUE_SIZE;
        q->processes[curr] = q->processes[next];
    }
    q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
    q->size--;
    
    return highest;
}