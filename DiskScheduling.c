#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define HIGH 199
#define LOW 0

void fcfsDiskScheduling(int q_size, int queue[], int head) {
int seek = 0, diff;
float avg;

printf("FCFS Disk Scheduling Algorithm\n");

for (int j = 0; j < q_size; j++) {
diff = abs(queue[j] - head);
seek += diff;
printf("Move from %d to %d with Seek %d\n", head, queue[j], diff);
head = queue[j];
}

printf("\nTotal seek time is %d\n", seek);
avg = seek / (float)q_size;

printf("Average seek time is %f\n", avg);
}

void cScanDiskScheduling(int q_size, int queue[], int head) {
int seek = 0, diff, i, j;
float avg;

printf("C-SCAN Disk Scheduling Algorithm\n");

int queue1[20], queue2[20], temp1 = 0, temp2 = 0;
for (int i = 0; i < q_size; i++) {
if (queue[i] >= head) {
queue1[temp1] = queue[i];
temp1++;
} else {
queue2[temp2] = queue[i];
temp2++;
}
}

for(i=0; i<temp1-1; i++){
for(j=i+1; j<temp1; j++){
if(queue1[i] > queue1[j]){
int temp = queue1[i];
queue1[i] = queue1[j];
queue1[j] = temp;
}
}
}

for(i=0; i<temp2-1; i++){
for(j=i+1; j<temp2; j++){
if(queue2[i]>queue2[j]){
int temp = queue2[i];
queue2[i] = queue2[j];
queue2[j] = temp;
}
}
}

//calculate closest edge
if(abs(head-LOW) >= abs(head-HIGH)){

for(i=1,j=0; j<temp1; i++,j++){
queue[i] = queue1[j];
}

queue[i] = HIGH;
queue[i+1] = 0;

for(i=temp1+3, j=0; j<temp2; i++, j++){
queue[i] = queue2[j];
}

} else {

for(i=1,j=temp2-1; j>=0; i++,j--){
queue[i] = queue2[j];
}

queue[i] = LOW;
queue[i+1] = HIGH;

for(i=temp2+3, j=temp1-1; j>=0; i++, j--){
queue[i] = queue1[j];
}
}

queue[0] = head;

for(j=0; j<=q_size+1; j++){
diff=abs(queue[j+1] - queue[j]);
seek += diff;
printf("Disk head moves from %d to %d with seek %d\n",queue[j],queue[j+1],diff);

}

//seek = seek - max; //subtract seek time back to zero
printf("Total seek time is %d\n", seek);
avg = seek/(float)q_size;
printf("Average seek time is %f\n", avg);
}

int findSSTF(int q_size, int queue[], int init) {
int *requestString = (int *)malloc(q_size * sizeof(int));
for (int i = 0; i < q_size; i++) {
requestString[i] = queue[i];
}

int head_movements = 0;
int temp = init;
int min_dis_idx;

printf("SSTF Disk Scheduling Algorithm\n");

for (int i = 0; i < q_size - 1; i++) {
min_dis_idx = i;

for (int j = i + 1; j < q_size; j++) {
if (abs(requestString[min_dis_idx] - temp) >= abs(requestString[j] - temp)) {
min_dis_idx = j;
}
}

head_movements += abs(requestString[min_dis_idx] - temp);
temp = requestString[min_dis_idx];

if (min_dis_idx != i) {
int temp1 = requestString[min_dis_idx];
requestString[min_dis_idx] = requestString[i];
requestString[i] = temp1;
}
}

head_movements += abs(requestString[q_size - 1] - temp);

printf("Modified request sequence: ");
for (int i = 0; i < q_size; i++) {
printf("%d ", requestString[i]);
}
printf("\nThe total number of head movements is: %d\n", head_movements);

free(requestString);

return head_movements;

}

int main() {
int choice, q_size, head;

printf("Disk Scheduling Algorithms Menu\n");
printf("Enter the size of the queue: ");
scanf("%d", &q_size);

int queue[q_size];
printf("Enter queue elements:\n");
for (int i = 0; i < q_size; i++) {
scanf("%d", &queue[i]);
}

printf("Enter initial head position: ");
scanf("%d", &head);

do {
printf("\n1. FCFS Disk Scheduling\n");
printf("2. SSTF Disk Scheduling\n");
printf("3. C-SCAN Disk Scheduling\n");
printf("4. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);

switch (choice) {
case 1:
fcfsDiskScheduling(q_size, queue, head);
break;
case 2:
findSSTF(q_size, queue, head);

break;
case 3:
cScanDiskScheduling(q_size, queue, head);
break;
case 4:
printf("Exiting the program. Goodbye!\n");
break;
default:
printf("Invalid choice. Please try again.\n");
}
} while (choice != 4);

return 0;
}
