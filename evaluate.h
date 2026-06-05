#ifndef EVALUATE_H
#define EVALUATE_H

#include "types.h"

float average_wait_time();
float average_turnaround_time();
float average_response_time();
float average_completion_time();
int longest_wait_time();
int longest_turnaround_time();
int longest_response_time();
int latest_completion_time();
int shortest_wait_time();
int shortest_turnaround_time();
int shortest_response_time();
int earliest_completion_time();
float wait_time_variance();
float turnaround_time_variance();
float response_time_variance();
float completion_time_variance();
int first_arrival_time();
int total_cpu_burst_time();
float cpu_utilization_rate();
float throughput_rate();
int total_idle_time();
int total_io_time();
int count_context_switches();

void print_gantt_chart();
void print_process_summary();
void report_algorithm_result(char* algorithm);
void compare_algorithm_results();

#endif