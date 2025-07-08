#include<stdio.h>
struct process
{
int at,bt,wt,tt,rt;
int completed;
float ntt;
} p[10];
int n, q[10], front=-1,rear=-1;
void enqueue(int i)
{
rear++;
q[rear]=i;
if(front==-1)
front=0;
}
int dequeue()
{
int temp=q[front];
if(front==rear)
front=rear=-1;
else
front++;
return temp;
}
int isInQueue(int i)
{
int k;
for(k=front; k<=rear; k++)
{
if(q[k]==i)
return 1;
}
return 0;
}
void sortByArrival()
{
struct process temp;

int i,j;
for(i=0; i<n-1; i++)
for(j=i+1; j<n; j++)
{
if(p[i].at>p[j].at)
{
temp=p[i];
p[i]=p[j];
p[j]=temp;
}
}
}
void main()
{
int i,j,time=0,sum_bt=0,tq;
float avgwt=0, avgtt=0;
printf("Enter number of processes:");
scanf("%d",&n);
for(i=0; i<n; i++)
{
printf("\nEnter the arrival time of process %d: ",i+1);
scanf("%d",&p[i].at);
}
for(i=0; i<n; i++)
{
printf("\nEnter the burst time of process %d: ",i+1);
scanf("%d",&p[i].bt);
p[i].rt=p[i].bt;
p[i].completed=0;
sum_bt+=p[i].bt;
}
printf("\nEnter the time quantum:");
scanf("%d",&tq);
sortByArrival();
enqueue(0);
for(time=p[0].at; time<sum_bt;)
{
i=dequeue();
if(p[i].rt<=tq)
{
time+=p[i].rt;
p[i].rt=0;
p[i].completed=1;

p[i].wt=time-p[i].at-p[i].bt;
p[i].tt=time-p[i].at;
p[i].ntt=((float)p[i].tt/p[i].bt);
for(j=0; j<n; j++)
{
if(p[j].at<=time && p[j].completed!=1&& isInQueue(j)!=1)
{
enqueue(j);
}
}
}
else
{
time+=tq;
p[i].rt-=tq;
for(j=0; j<n; j++)
{
if(p[j].at<=time && p[j].completed!=1&&i!=j&& isInQueue(j)!=1)
{
enqueue(j);
}
}
enqueue(i);
}
}
printf("\nName\tArrival Time\tBurst Time\tWaiting Time\tTurnAround Time");
for(i=0; i<n; i++)
{
avgwt+=p[i].wt;
avgtt+=p[i].tt;
printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d",i+1,p[i].at,p[i].bt,p[i].wt,p[i].tt);
}
printf("\nAverage waiting time:%f\n",avgwt/n);
printf("\nAverage waiting time:%f\n",avgtt/n);
}
