#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10

void fifo(int n, int frameSize, int pageRequests[]);
void lru(int n, int frameSize, int pageRequests[]);
void optimal(int n, int frameSize, int pageRequests[]);

int main() {
int n;
int frameSize;
int pageRequests[MAX_FRAMES];

printf("Enter the number of page requests: ");
scanf("%d", &n);

printf("Enter the frame size: ");
scanf("%d", &frameSize);

printf("Enter the page requests:\n");

for (int i = 0; i < n; i++) {
scanf("%d", &pageRequests[i]);
}

int choice;
do {
printf("\nPage Replacement Algorithms Menu:\n");
printf("1. FIFO\n");
printf("2. LRU\n");
printf("3. Optimal\n");
printf("4. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);

switch (choice) {
case 1:
fifo(n, frameSize, pageRequests);
break;
case 2:
lru(n, frameSize, pageRequests);
break;
case 3:
optimal(n, frameSize, pageRequests);
break;
case 4:
printf("Exiting the program.\n");
break;
default:
printf("Invalid choice. Please select a valid option.\n");
}
} while (choice != 4);

return 0;
}

void displayFrames(int frameSize, int frames[]) {
printf("Frames: ");
for (int j = 0; j < frameSize; j++) {
if (frames[j] == -1) {
printf("- ");
} else {
printf("%d ", frames[j]);
}
}
printf("\n");
}

void fifo(int n, int frameSize, int pageRequests[]) {
int frames[MAX_FRAMES];
int pageFaults = 0;
int frameIndex = 0;

for (int i = 0; i < frameSize; i++) {
frames[i] = -1;
}

for (int i = 0; i < n; i++) {
int page = pageRequests[i];
bool pageFound = false;

for (int j = 0; j < frameSize; j++) {
if (frames[j] == page) {
pageFound = true;
break;

}
}

if (!pageFound) {
frames[frameIndex] = page;
frameIndex = (frameIndex + 1) % frameSize;
pageFaults++;
}

displayFrames(frameSize, frames);
}

printf("FIFO Page Faults: %d\n", pageFaults);
}

void lru(int n, int frameSize, int pageRequests[]) {
int frames[MAX_FRAMES];
int pageFaults = 0;
int frameIndex = 0;
int recent[MAX_FRAMES];

for (int i = 0; i < frameSize; i++) {
frames[i] = -1;
recent[i] = 0;
}

for (int i = 0; i < n; i++) {
int page = pageRequests[i];
bool pageFound = false;

for (int j = 0; j < frameSize; j++) {
if (frames[j] == page) {

pageFound = true;
recent[j] = i;
break;
}
}

if (!pageFound) {
int replaceIndex = 0;
for (int j = 1; j < frameSize; j++) {
if (recent[j] < recent[replaceIndex]) {
replaceIndex = j;
}
}

frames[replaceIndex] = page;
recent[replaceIndex] = i;
pageFaults++;
}

displayFrames(frameSize, frames);
}

printf("LRU Page Faults: %d\n", pageFaults);
}

void optimal(int n, int frameSize, int pageRequests[]) {
int frames[MAX_FRAMES];
int pageFaults = 0;

for (int i = 0; i < frameSize; i++) {
frames[i] = -1;
}

for (int i = 0; i < n; i++) {
int page = pageRequests[i];
bool pageFound = false;

for (int j = 0; j < frameSize; j++) {
if (frames[j] == page) {
pageFound = true;
break;
}
}

if (!pageFound) {
int replaceIndex = -1;

for (int j = 0; j < frameSize; j++) {
int k;
for (k = i + 1; k < n; k++) {
if (pageRequests[k] == frames[j]) {
replaceIndex = j;
break;
}
}

if (k == n) {
replaceIndex = j;
break;
}
}

if (replaceIndex != -1) {
frames[replaceIndex] = page;

pageFaults++;
}
}

displayFrames(frameSize, frames);
}

printf("Optimal Page Faults: %d\n", pageFaults);
}
