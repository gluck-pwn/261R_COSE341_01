#ifndef PROCESS_H
#define PROCESS_H

#include "types.h"

void restore_process_snapshot();

void add_process_record(int pid, int arrival_time, int burst_time, int priority, int io_count, int* request_times, int* burst_times);
void add_random_process_record(int pid);
void load_process_records(int choice);

void show_process_record(Process *p);

#endif
