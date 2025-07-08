//non pre emptive
#include <stdio.h>
#include <string.h>
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
int main() {
int n;
struct process p[100];
float avg_turnaround_time;
float avg_waiting_time;
int total_turnaround_time = 0;
int total_waiting_time = 0;
int total_response_time = 0;
int total_idle_time = 0;
int is_completed[100];
memset(is_completed, 0, sizeof(is_completed));
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
int current_time = 0;
int completed = 0;
int prev = 0;
while (completed != n) {

int idx = -1;
int mn = 10000000;
for (int i = 0; i < n; i++) {
if (p[i].arrival_time <= current_time && is_completed[i] == 0) {
if (p[i].burst_time < mn) {
mn = p[i].burst_time;
idx = i;
}
if (p[i].burst_time == mn) {
if (p[i].arrival_time < p[idx].arrival_time) {
mn = p[i].burst_time;
idx = i;
}
}
}
}
if (idx != -1) {
p[idx].start_time = current_time;
p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
p[idx].response_time = p[idx].start_time - p[idx].arrival_time;
total_turnaround_time += p[idx].turnaround_time;
total_waiting_time += p[idx].waiting_time;
total_response_time += p[idx].response_time;
total_idle_time += p[idx].start_time - prev;
is_completed[idx] = 1;
completed++;
current_time = p[idx].completion_time;
prev = current_time;
} else {
current_time++;
}
}
int min_arrival_time = 10000000;
int max_completion_time = -1;
for (int i = 0; i < n; i++) {
min_arrival_time = (p[i].arrival_time < min_arrival_time) ? p[i].arrival_time :
min_arrival_time;
max_completion_time = (p[i].completion_time > max_completion_time) ?
p[i].completion_time : max_completion_time;
}
avg_turnaround_time = (float)total_turnaround_time / n;
avg_waiting_time = (float)total_waiting_time / n;
printf("\n\n");
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
