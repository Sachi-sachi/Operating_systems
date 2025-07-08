#include <stdio.h>
#include <stdlib.h>
struct process {
int pid;
int arrival_time;
int burst_time;
int start_time;
int completion_time;
int turnaround_time;
int waiting_time;
int response_time;
};
int compareArrival(const void *a, const void *b)
{
return ((struct process*)a)->arrival_time - ((struct process*)b)->arrival_time;
}
int compareID(const void *a, const void *b)
{
return ((struct process*)a)->pid - ((struct process*)b)->pid;
}
int main() {
int n;
struct process p[100];
float avg_turnaround_time;
float avg_waiting_time;
int total_turnaround_time = 0;
int total_waiting_time = 0;
int total_response_time = 0;
int total_idle_time = 0;
printf("Enter the number of processes: ");

scanf("%d", &n);
for (int i = 0; i < n; i++) {
printf("Enter arrival time of process %d: ", i + 1);
scanf("%d", &p[i].arrival_time);
printf("Enter burst time of process %d: ", i + 1);
scanf("%d", &p[i].burst_time);
p[i].pid = i + 1;
printf("\n");
}
qsort(p, n, sizeof(struct process), compareArrival);
for (int i = 0; i < n; i++) {
p[i].start_time = (i == 0) ? p[i].arrival_time : (p[i - 1].completion_time >
p[i].arrival_time ? p[i - 1].completion_time : p[i].arrival_time);
p[i].completion_time = p[i].start_time + p[i].burst_time;
p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
p[i].response_time = p[i].start_time - p[i].arrival_time;
total_turnaround_time += p[i].turnaround_time;
total_waiting_time += p[i].waiting_time;
total_response_time += p[i].response_time;
total_idle_time += (i == 0) ? (p[i].arrival_time) : (p[i].start_time - p[i -
1].completion_time);
}
avg_turnaround_time = (float) total_turnaround_time / n;
avg_waiting_time = (float) total_waiting_time / n;
qsort(p, n, sizeof(struct process), compareID);
printf("\n");
printf("#P\tAT\tBT\tST\tCT\tTAT\tWT\tRT\t\n\n");
for (int i = 0; i < n; i++) {
printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\n", p[i].pid, p[i].arrival_time,
p[i].burst_time, p[i].start_time, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time,
p[i].response_time);
}
printf("Average Turnaround Time = %.2f\n", avg_turnaround_time);
printf("Average Waiting Time = %.2f\n", avg_waiting_time);
return 0;
}
/*
AT - Arrival Time of the process
BT - Burst time of the process
ST - Start time of the process

CT - Completion time of the process
TAT - Turnaround time of the process
WT - Waiting time of the process
RT - Response time of the process
Formulas used:
TAT = CT - AT
WT = TAT - BT
RT = ST - AT
*/
