#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "types.h"
#include "process.h"
#include "io.h"
#include "queue.h"
#include "scheduler.h"
#include "evaluate.h"

Process processes[MAX_PROCESSES];
Process current_processes[MAX_PROCESSES];
int num_processes = 0;
int completed_processes = 0;
Queue ready_queue;
Queue waiting_queue;
GanttItem gantt[MAX_TIME];
int num_gantt_items = 0;
EvalItem evaluation[NUM_ALGORITHMS];
int num_simulation = 0;

int main(){
    srand(time(NULL));
    int choice, number;
    printf("CPU Scheduling Simulator\n");
    printf("========================================\n");
    printf("1. Sample\n");
    printf("2. Random\n");
    printf("3. From file\n");
    printf("4. Manual input\n");
    printf("========================================\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    load_process_records(choice);

    restore_process_snapshot();
    
    if (choice != 4){
        for (int i = 0; i < num_processes; i++){
            show_process_record(&current_processes[i]);
        }
    }
    printf("\n\n");
    
    printf("\nRunning FCFS\n");
    simulate_fcfs();
    report_algorithm_result("FCFS");

    printf("\nRunning SJF\n");
    simulate_sjf_preemptive();
    report_algorithm_result("Preemptive SJF");

    printf("\nRunning SJF Non-Preemptive\n");
    simulate_sjf_nonpreemptive();
    report_algorithm_result("Nonpreemptive SJF");

    printf("\nRunning Priority\n");
    simulate_priority_preemptive();
    report_algorithm_result("Preemptive Priority");

    printf("\nRunning Priority Non-Preemptive\n");
    simulate_priority_nonpreemptive();
    report_algorithm_result("Nonpreemptive Priority");
    
    printf("\nRunning RR\n");
    simulate_round_robin();
    report_algorithm_result("RR");

    printf("\nRunning Aging Priority\n");
    simulate_aging_priority_preemptive();
    report_algorithm_result("Aging Preemptive Priority");

    printf("\nRunning Aging Priority Non-Preemptive\n");
    simulate_aging_priority_nonpreemptive();
    report_algorithm_result("Aging Nonpreemptive Priority");

    printf("\nRunning HRRN\n");
    simulate_hrrn_preemptive();
    report_algorithm_result("Preemptive HRRN");

    printf("\nRunning HRRN Non-Preemptive\n");
    simulate_hrrn_nonpreemptive();
    report_algorithm_result("Nonpreemptive HRRN");

    printf("\nRunning CFS\n");
    simulate_cfs_preemptive();
    report_algorithm_result("Preemptive CFS");

    printf("\nRunning CFS Non-Preemptive\n");
    simulate_cfs_nonpreemptive();
    report_algorithm_result("Nonpreemptive CFS");

    compare_algorithm_results();
    return 0;
}
