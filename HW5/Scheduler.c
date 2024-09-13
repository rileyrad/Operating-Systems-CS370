#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_duration;
    int priority;

    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;

int process_count(FILE *file) {
    int count = 0;
    char c;

    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            count++;
        }
    }

    fclose(file);
    return count;
}

void read_file(char *filename, Process processes[], int n) {
    FILE *file = fopen(filename, "r");

    int i = 0;
    while (i < n && fscanf(file, "%d,%d,%d,%d", &processes[i].pid, &processes[i].arrival_time, &processes[i].burst_duration, &processes[i].priority) != EOF) {
        processes[i].remaining_time = processes[i].burst_duration;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        i++;
    }

    fclose(file);
}

void calculate_metrics(Process processes[], int n, double *avg_turnaround, double *avg_waiting, double *throughput) {
    int turnaround_sum, waiting_sum, burst_sum = 0;

    for (int i = 0; i < n; i++) {
        turnaround_sum += processes[i].turnaround_time;
        waiting_sum += processes[i].waiting_time;
        burst_sum += processes[i].burst_duration;
    }

    *avg_turnaround = (double) turnaround_sum / n;
    *avg_waiting = (double) waiting_sum / n;
    *throughput = (double) n / burst_sum;
}

int sort_arrival_time(const void *arg_p1, const void *arg_p2) {
    Process *p1 = (Process *)arg_p1;
    Process *p2 = (Process *)arg_p2;

    return p1->arrival_time - p2->arrival_time;
}

void fcfs(Process processes[], int n) {
    Process process[n];
    int time = 0;

    memcpy(process, processes, n * sizeof(Process));
    qsort(process, n, sizeof(Process), sort_arrival_time);

    for (int i = 0; i < n; i++) {
        if (time < process[i].arrival_time) {
            time = process[i].arrival_time;
        }
        process[i].waiting_time = time - process[i].arrival_time;
        time += process[i].burst_duration;
        process[i].turnaround_time = time - process[i].arrival_time;
    }

    // ---- OUTPUT ----
    double avg_turnaround, avg_waiting, throughput;
    calculate_metrics(process, n, &avg_turnaround, &avg_waiting, &throughput);

    printf("--- FCFS ---\n");
    printf("Average Turnaround Time: %.3f\n", avg_turnaround);
    printf("Average Waiting Time: %.3f\n", avg_waiting);
    printf("Throughput: %.3f\n", throughput);
}

void sjf(Process processes[], int n) {
    Process process[n];
    memcpy(process, processes, n * sizeof(Process));

    int time = 0;
    int completed = 0;
    bool in_progress = false;
    int current_pid = -1;
    int shortest_remaining_time;

    while (completed < n) {
        shortest_remaining_time = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (process[i].arrival_time <= time && process[i].remaining_time > 0 && process[i].remaining_time < shortest_remaining_time) {
                shortest_remaining_time = process[i].remaining_time;
                current_pid = i;
                in_progress = true;
            }
        }

        // ---- PREEMPTION ----
        if (in_progress) {
            process[current_pid].remaining_time--;

            for (int i = 0; i < n; i++) {
                if (i != current_pid && process[i].arrival_time <= time && process[i].remaining_time > 0) {
                    process[i].waiting_time++;
                }
            }

            if (process[current_pid].remaining_time == 0) {
                process[current_pid].turnaround_time = time + 1 - process[current_pid].arrival_time;
                completed++;
                in_progress = false;
            }
        }

        time++;
    }

    // ---- OUTPUT ----
    double turnaround, waiting, throughput;
    calculate_metrics(process, n, &turnaround, &waiting, &throughput);

    printf("--- SJFP ---\n");
    printf("Average Turnaround Time: %.3f\n", turnaround);
    printf("Average Waiting Time: %.3f\n", waiting);
    printf("Throughput: %.3f\n", throughput);
}

void priority(Process processes[], int n) {
    Process process[n];
    memcpy(process, processes, n * sizeof(Process));

    int time = 0;
    int completed = 0;
    bool in_progress = false;
    int current_pid = -1;
    int highest_priority;

    while (completed < n) {
        highest_priority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (process[i].arrival_time <= time && process[i].remaining_time > 0 && process[i].priority < highest_priority) {
                highest_priority = process[i].priority;
                current_pid = i;
                in_progress = true;
            }
        }

        // ---- PREEMPTION ----
        if (in_progress) {
            process[current_pid].remaining_time--;

            for (int i = 0; i < n; i++) {
                if (i != current_pid && process[i].arrival_time <= time && process[i].remaining_time > 0) {
                    process[i].waiting_time++;
                }
            }

            if (process[current_pid].remaining_time == 0) {
                process[current_pid].turnaround_time = time + 1 - process[current_pid].arrival_time;
                completed++;
                in_progress = false;
            }
        }
        time++;
    }

    // ---- OUTPUT ----
    double turnaround, waiting, throughput;
    calculate_metrics(process, n, &turnaround, &waiting, &throughput);

    printf("--- Priority ---\n");
    printf("Average Turnaround Time: %.3f\n", turnaround);
    printf("Average Waiting Time: %.3f\n", waiting);
    printf("Throughput: %.3f\n", throughput);
}

int main(int argc, char *argv[]) {
    char* filename = argv[1];

    FILE *file = fopen(filename, "r");
    int n = process_count(file);
    Process processes[n];
    read_file(filename, processes, n);

    fcfs(processes, n);
    sjf(processes, n);
    priority(processes, n);

    return 0;
}