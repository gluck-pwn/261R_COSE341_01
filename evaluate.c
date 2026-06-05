#include "evaluate.h"
#include "process.h"
#include "scheduler.h"
#include <stdio.h>

float average_wait_time(){
    float total_waiting_time = 0;
    for (int i = 0; i < num_processes; i++){
        total_waiting_time += current_processes[i].waiting_time;
    }
    return total_waiting_time / num_processes;
}
float average_turnaround_time(){
    float total_turnaround_time = 0;
    for (int i = 0; i < num_processes; i++){
        total_turnaround_time += current_processes[i].turnaround_time;
    }
    return total_turnaround_time / num_processes;
}
float average_response_time(){
    float total_response_time = 0;
    for (int i = 0; i < num_processes; i++){
        total_response_time += current_processes[i].response_time;
    }
    return total_response_time / num_processes;
}
float average_completion_time(){
    float total_completion_time = 0;
    for (int i = 0; i < num_processes; i++){
        total_completion_time += current_processes[i].completion_time;
    }
    return total_completion_time / num_processes;
}

int longest_wait_time(){
    int max_waiting_time = 0;
    for (int i = 0; i < num_processes; i++){
        if (current_processes[i].waiting_time > max_waiting_time){
            max_waiting_time = current_processes[i].waiting_time;
        }
    }
    return max_waiting_time;
}
int longest_turnaround_time(){
    int max_turnaround_time = 0;
    for (int i = 0; i < num_processes; i++){
        if (current_processes[i].turnaround_time > max_turnaround_time){
            max_turnaround_time = current_processes[i].turnaround_time;
        }
    }
    return max_turnaround_time;
}
int longest_response_time(){
    int max_response_time = 0;
    for (int i = 0; i < num_processes; i++){
        if (current_processes[i].response_time > max_response_time){
            max_response_time = current_processes[i].response_time;
        }
    }
    return max_response_time;
}
int latest_completion_time(){
    int max_completion_time = 0;
    for (int i = 0; i < num_processes; i++){
        if (current_processes[i].completion_time > max_completion_time){
            max_completion_time = current_processes[i].completion_time;
        }
    }
    return max_completion_time;
}

int shortest_wait_time(){
    int min_waiting_time = MAX_TIME;
    for (int i = 0; i< num_processes; i++){
        if (current_processes[i].waiting_time < min_waiting_time){
            min_waiting_time = current_processes[i].waiting_time;
        }
    }
    return min_waiting_time;
}
int shortest_turnaround_time(){
    int min_turnaround_time = MAX_TIME;
    for (int i = 0; i < num_processes; i++){
        if (current_processes[i].turnaround_time < min_turnaround_time){
            min_turnaround_time = current_processes[i].turnaround_time;
        }
    }
    return min_turnaround_time;
}
int shortest_response_time(){
    int min_response_time = MAX_TIME;
    for (int i = 0; i < num_processes; i++){
        if (current_processes[i].response_time < min_response_time){
            min_response_time = current_processes[i].response_time;
        }
    }
    return min_response_time;
}
int earliest_completion_time(){
    int min_completion_time = MAX_TIME;
    for (int i = 0; i < num_processes; i++){
        if (current_processes[i].completion_time < min_completion_time){
            min_completion_time = current_processes[i].completion_time;
        }
    }
    return min_completion_time;
}

float wait_time_variance(){
    float average = average_wait_time();
    float sum = 0.0;
    for (int i = 0; i < num_processes; i++){
        float difference = current_processes[i].waiting_time - average;
        sum += difference * difference;
    }
    return sum / num_processes;
}
float turnaround_time_variance(){
    float average = average_turnaround_time();
    float sum = 0.0;
    for (int i = 0; i < num_processes; i++){
        float difference = current_processes[i].turnaround_time - average;
        sum += difference * difference;
    }
    return sum / num_processes;
}
float response_time_variance(){
    float average = average_response_time();
    float sum = 0.0;
    for (int i = 0; i < num_processes; i++){
        float difference = current_processes[i].response_time - average;
        sum += difference * difference;
    }
    return sum / num_processes;
}
float completion_time_variance(){
    float average = average_completion_time();
    float sum = 0.0;
    for (int i = 0; i < num_processes; i++){
        float difference = current_processes[i].completion_time - average;
        sum += difference * difference;
    }
    return sum / num_processes;
}

int first_arrival_time(){
    int first_arrival = MAX_TIME;
    for (int i = 0; i < num_processes; i++){
        if (current_processes[i].arrival_time < first_arrival){
            first_arrival= current_processes[i].arrival_time;
        }
    }
    return first_arrival;
}
int total_cpu_burst_time(){
    int sum = 0;
    for (int i = 0; i < num_processes; i++){
        sum += current_processes[i].burst_time;
    }
    return sum;
}
float cpu_utilization_rate(){
    return (float)total_cpu_burst_time() / (latest_completion_time() - first_arrival_time());
}
float throughput_rate(){
    return (float)num_processes / (latest_completion_time() - first_arrival_time());
}
int total_idle_time(){
    return latest_completion_time() - total_cpu_burst_time() - first_arrival_time();
}
int total_io_time(){
    int sum = 0;
    for (int i = 0; i < num_processes; i++){
        for (int j = 0; j < current_processes[i].io_count; j++){
            sum += current_processes[i].io[j].io_time;
        }
    }
    return sum;
}

int count_context_switches(){
    int context_switch = 0;
    for (int i = 0; i < num_gantt_items - 1; i++){
        if (gantt[i].pid != gantt[i + 1].pid){
            context_switch++;
        }
    }
    return context_switch;
}


void print_gantt_chart(){
    printf("\nGantt chart\n");
    printf("========================================\n\n");
    if (gantt[0].start_time != 0){
        printf("|  idle  |");
    } else{
        printf("|");
    }
    for (int i = 0; i < num_gantt_items ; i++){
        printf("   P%-3d |", gantt[i].pid);
        if(gantt[i].end_time != gantt[i+1].start_time){
            printf("  idle  |");
        }
    }
    if (gantt[0].start_time != 0){
        printf("\n0\t ");
    } else{
        printf("\n");
    }
    for (int i = 0; i < num_gantt_items ; i++){
        if(gantt[i].end_time != gantt[i+1].start_time){
            printf("%-5d%5d", gantt[i].start_time, gantt[i].end_time);
            printf("        ");
        }
        else{
            printf("%-9d", gantt[i].start_time);
        }
    }
    printf("fin\n\n");
}

void print_process_summary(){
    printf("\nProcess table\n");
    printf("========================================\n");
    printf("PID\tState\t\tArrival\tBurst\tPriority\tIO count\tCompletion\tTurnaround\tWaiting\t\tResponse\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < num_processes; i++){
        Process *p = &current_processes[i];
        char* state;
        switch (p->state){
            case READY:
                state = "READY";
                break;
            case RUNNING:
                state = "RUNNING";
                break;
            case WAITING:
                state = "WAITING";
                break;
            case TERMINATED:
                state = "TERMINATED";
                break;
        }
        if (p->state != TERMINATED){
            printf("%d\t%s\t\t%d\t%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p->pid, state, p->arrival_time, p->burst_time, p->priority, p->io_count, p->completion_time, p->turnaround_time, p->waiting_time, p->response_time);
        }
        else{
            printf("%d\t%s\t%d\t%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p->pid, state, p->arrival_time, p->burst_time, p->priority, p->io_count, p->completion_time, p->turnaround_time, p->waiting_time, p->response_time);
        }
    }
    
    printf("\n\n");
}

void report_algorithm_result(char* algorithm){
    int idx = num_simulation - 1;

    print_gantt_chart();
    print_process_summary();
    printf("Average waiting time: %.2f\tMax: %2d, Min:%2d, Variance: %.2f\n", average_wait_time(), longest_wait_time(), shortest_wait_time(), wait_time_variance());
    printf("Average turnaround time: %.2f\tMax: %2d, Min:%2d, Variance: %.2f\n", average_turnaround_time(), longest_turnaround_time(), shortest_turnaround_time(), turnaround_time_variance());
    printf("Average response time: %.2f\tMax: %2d, Min:%2d, Variance: %.2f\n", average_response_time(), longest_response_time(), shortest_response_time(), response_time_variance());
    printf("Average completion time: %.2f\tMax: %2d, Min:%2d, Variance: %.2f\n", average_completion_time(), latest_completion_time(), earliest_completion_time(), completion_time_variance());
    printf("CPU Utilization: %.2f%%\n", 100.0 * cpu_utilization_rate());
    printf("Throughput: %.2f process per 100s\n", 100.0 * throughput_rate());
    printf("CPU time: %d\n", total_cpu_burst_time());
    printf("IO time: %d\n", total_io_time());
    printf("Idle time: %d\n", total_idle_time());
    printf("Total time: %d\n", latest_completion_time() - first_arrival_time());
    printf("Context switch: %d times\n", count_context_switches());
    printf("\n========================================\n\n");

    evaluation[idx].algorithm = algorithm;
    evaluation[idx].average_waiting_time = average_wait_time();
    evaluation[idx].average_turnaround_time = average_turnaround_time();
    evaluation[idx].average_response_time = average_response_time();
    evaluation[idx].max_completion_time = latest_completion_time();
    evaluation[idx].variance_waiting_time = wait_time_variance();
    evaluation[idx].cpu_utilization = cpu_utilization_rate();
    evaluation[idx].throughput = throughput_rate();
    evaluation[idx].idle_time = total_idle_time();
    evaluation[idx].context_switch = count_context_switches();
    evaluation[idx].shortest_waiting = 0;
    evaluation[idx].shortest_turnaround = 0;
    evaluation[idx].shortest_response = 0;
    evaluation[idx].shortest_completion = 0;
    evaluation[idx].smallest_variance = 0;
    evaluation[idx].min_context_switch = 0;
}

void compare_algorithm_results(){
    float average_waiting = 0;
    float average_turnaround = 0;
    float average_response = 0;
    float average_completion = 0;
    float average_variance = 0;
    float average_cpu_utilization = 0;
    float average_throughput = 0;
    float average_context_switch = 0;
    float average_idle_time = 0;
    float improvement;
    int count = 0;

    for (int i = 0; i < NUM_ALGORITHMS; i++){
        average_waiting += evaluation[i].average_waiting_time;
        average_turnaround += evaluation[i].average_turnaround_time;
        average_response += evaluation[i].average_response_time;
        average_completion += evaluation[i].max_completion_time;
        average_variance += evaluation[i].variance_waiting_time;
        average_cpu_utilization += evaluation[i].cpu_utilization;
        average_throughput += evaluation[i].throughput;
        average_context_switch += evaluation[i].context_switch;
        average_idle_time += evaluation[i].idle_time;
    }
    average_waiting /= NUM_ALGORITHMS;
    average_turnaround /= NUM_ALGORITHMS;
    average_response /= NUM_ALGORITHMS;
    average_completion /= NUM_ALGORITHMS;
    average_variance /= NUM_ALGORITHMS;
    average_cpu_utilization /= NUM_ALGORITHMS;
    average_throughput /= NUM_ALGORITHMS;
    average_context_switch /= NUM_ALGORITHMS;
    average_idle_time /= NUM_ALGORITHMS;

    printf("\n\nComparation\n");
    printf("========================================\n");

    for (int i = 0; i < NUM_ALGORITHMS; i++){
        for (int j = 0; j < NUM_ALGORITHMS; j++)
        if (evaluation[i].average_waiting_time > evaluation[j].average_waiting_time){
            evaluation[i].shortest_waiting++;
        }
    }
    for (int i = 0; i < NUM_ALGORITHMS; i++){
        if (evaluation[i].shortest_waiting == 0){
            printf("%s has shortest average waiting time: %.2f\n", evaluation[i].algorithm, evaluation[i].average_waiting_time);
            improvement = 100 * (average_waiting - evaluation[i].average_waiting_time) / average_waiting;
            count++;
        }
    }
    if (count != NUM_ALGORITHMS){
        printf("%.0f%% shorter than average (%.2f)\n\n", improvement, average_waiting);
    } else{
        printf("All algorithms have same average waiting time\n\n");
    }
    count = 0;

    for (int i = 0; i < NUM_ALGORITHMS; i++){
        for (int j = 0; j < NUM_ALGORITHMS; j++)
        if (evaluation[i].average_turnaround_time > evaluation[j].average_turnaround_time){
            evaluation[i].shortest_turnaround++;
        }
    }
    for (int i = 0; i < NUM_ALGORITHMS; i++){
        if (evaluation[i].shortest_turnaround == 0){
            printf("%s has shortest average turnaround time: %.2f\n", evaluation[i].algorithm, evaluation[i].average_turnaround_time);
            improvement = 100 * (average_turnaround - evaluation[i].average_turnaround_time) / average_turnaround;
            count++;
        }
    }
    if (count != NUM_ALGORITHMS){
        printf("%.0f%% shorter than average (%.2f)\n\n", improvement, average_turnaround);
    } else{
        printf("All algorithms have same average turnaround time\n\n");
    }
    count = 0;

    for (int i = 0; i < NUM_ALGORITHMS; i++){
        for (int j = 0; j < NUM_ALGORITHMS; j++)
        if (evaluation[i].average_response_time > evaluation[j].average_response_time){
            evaluation[i].shortest_response++;
        }
    }
    for (int i = 0; i < NUM_ALGORITHMS; i++){
        if (evaluation[i].shortest_response == 0){
            printf("%s has shortest average response time: %.2f\n", evaluation[i].algorithm, evaluation[i].average_response_time);
            improvement = 100 * (average_response - evaluation[i].average_response_time) / average_response;
            count++;
        }
    }
    if (count != NUM_ALGORITHMS){
        printf("%.0f%% shorter than average (%.2f)\n\n", improvement, average_response);
    } else{
        printf("All algorithms have same average response time\n\n");
    }
    count = 0;

    for (int i = 0; i < NUM_ALGORITHMS; i++){
        for (int j = 0; j < NUM_ALGORITHMS; j++)
        if (evaluation[i].max_completion_time > evaluation[j].max_completion_time){
            evaluation[i].shortest_completion++;
        }
    }
    for (int i = 0; i < NUM_ALGORITHMS; i++){
        if (evaluation[i].shortest_completion == 0){
            printf("%s has shortest max completion time: %d\n", evaluation[i].algorithm, evaluation[i].max_completion_time);
            improvement = 100 * (average_completion - evaluation[i].max_completion_time) / average_completion;
            count++;
        }
    }
    if (count != NUM_ALGORITHMS){
        printf("%.0f%% shorter than average (%.2f)\n\n", improvement, average_completion);
    } else{
        printf("All algorithms have same max completion time\n\n");
    }
    count = 0;

    for (int i = 0; i < NUM_ALGORITHMS; i++){
        for (int j = 0; j < NUM_ALGORITHMS; j++)
        if (evaluation[i].variance_waiting_time > evaluation[j].variance_waiting_time){
            evaluation[i].smallest_variance++;
        }
    }
    for (int i = 0; i < NUM_ALGORITHMS; i++){
        if (evaluation[i].smallest_variance == 0){
            printf("%s has smallest variance of waiting time: %.2f\n", evaluation[i].algorithm, evaluation[i].variance_waiting_time);
            improvement = 100 * (average_variance - evaluation[i].variance_waiting_time) / average_variance;
            count++;
        }
    }
    if (count != NUM_ALGORITHMS){
        printf("%.0f%% smaller than average (%.2f)\n\n", improvement, average_variance);
    } else{
        printf("All algorithms have same variance of waiting time\n\n");
    }
    count = 0;

    for (int i = 0; i < NUM_ALGORITHMS; i++){
        if (evaluation[i].shortest_completion == 0){
            printf("%s has highest cpu utilization: %.2f\n", evaluation[i].algorithm, evaluation[i].cpu_utilization);
            improvement = 100 * (evaluation[i].cpu_utilization - average_cpu_utilization) / average_cpu_utilization;
            count++;
        }
    }
    if (count != NUM_ALGORITHMS){
        printf("%.0f%% higher than average (%.2f)\n\n", improvement, average_cpu_utilization);
    } else{
        printf("All algorithms have same cpu utilization\n\n");
    }
    count = 0;

    for (int i = 0; i < NUM_ALGORITHMS; i++){
        if (evaluation[i].shortest_completion == 0){
            printf("%s has highest throughput: %.2f\n", evaluation[i].algorithm, evaluation[i].throughput);
            improvement = 100 * (evaluation[i].throughput - average_throughput) / average_throughput;
            count++;
        }
    }
    if (count != NUM_ALGORITHMS){
        printf("%.0f%% higher than average (%.2f)\n\n", improvement, average_throughput);
    } else{
        printf("All algorithms have same throughput\n\n");
    }
    count = 0;

    for (int i = 0; i < NUM_ALGORITHMS; i++){
        if (evaluation[i].shortest_completion == 0){
            printf("%s has smallest idle time: %d\n", evaluation[i].algorithm, evaluation[i].idle_time);
            improvement = 100 * (average_idle_time - evaluation[i].idle_time) / average_idle_time;
            count++;
        }
    }
    if (count != NUM_ALGORITHMS){
        printf("%.0f%% smaller than average (%.2f)\n\n", improvement, average_idle_time);
    } else{
        printf("All algorithms have same idle time\n\n");
    }
    count = 0;

    for (int i = 0; i < NUM_ALGORITHMS; i++){
        for (int j = 0; j < NUM_ALGORITHMS; j++)
        if (evaluation[i].context_switch > evaluation[j].context_switch){
            evaluation[i].min_context_switch++;
        }
    }
    for (int i = 0; i < NUM_ALGORITHMS; i++){
        if (evaluation[i].min_context_switch == 0){
            printf("%s has smallest context switch: %d\n", evaluation[i].algorithm, evaluation[i].context_switch);
            improvement = 100 * (average_context_switch - evaluation[i].context_switch) / average_context_switch;
            count++;
        }
    }
    if (count != NUM_ALGORITHMS){
        printf("%.0f%% smaller than average (%.2f)\n\n", improvement, average_context_switch);
    } else{
        printf("All algorithms have same context switch\n\n");
    }
}