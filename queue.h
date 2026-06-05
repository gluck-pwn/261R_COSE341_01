#ifndef QUEUE_H
#define QUEUE_H

#include "types.h"

void clear_queue(Queue *q);
void reset_scheduler_queues();
int queue_is_empty(Queue *q);
int queue_is_full(Queue *q);
void push_process(Queue *q, Process *p);
Process *pop_process(Queue *q);

void take_process_out(Queue *q, Process *p);

Process *pick_shortest_remaining_job(Queue *q);
Process *pick_highest_priority_job(Queue *q);

#endif