#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "types.h"

void reset_scheduler_run();

void move_to_io_if_requested();
void return_finished_io_jobs();
void admit_new_arrival(int i);
void start_cpu_slice();
void finish_current_process();
void yield_current_process();
void save_gantt_slice(int pid, int start_time, int end_time);
void tick_ready_and_waiting_queues();

void simulate_fcfs();
void simulate_sjf_preemptive();
void simulate_sjf_nonpreemptive();
void simulate_priority_preemptive();
void simulate_priority_nonpreemptive();
void simulate_round_robin();

void simulate_aging_priority_preemptive();
void simulate_aging_priority_nonpreemptive();
void simulate_hrrn_preemptive();
void simulate_hrrn_nonpreemptive();
void simulate_cfs_preemptive();
void simulate_cfs_nonpreemptive();

#endif