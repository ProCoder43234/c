#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct process
{
    int pid, arrival, burst, wait, turn;
    int temp;
} process;
int k = 0;
int *pid;
int *time;

void sort_arrival_time(process *p, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (p[min].arrival > p[j].arrival)
                min = j;
        }
        if (i != min)
        {
            process temp = p[i];
            p[i] = p[min];
            p[min] = temp;
        }
    }
}

void round_robin(process *p, int n, int quantum)
{
    int rem[n];
    for (int i = 0; i < n; i++)
        rem[i] = p[i].burst;
    int previous = p[0].arrival;
    while (1)
    {
        int flag = 0;
        int i;
        int min = 0;
        for (i = 0; i < n; i++)
        {
            if (rem[i] > 0)
            {
                if (p[i].temp <= p[min].temp)
                    min = i;
            }
        }
        if (rem[min] > 0)
        {
            flag = 1;
            if (rem[min] > quantum)
            {
                previous += quantum;
                rem[min] -= quantum;
            }
            else
            {
                previous += rem[min];
                p[min].wait = previous - p[min].burst - p[min].arrival;
                rem[min] = 0;
                p[min].turn = p[min].burst + p[min].wait;
            }
            p[min].temp = previous;
            pid[k] = p[min].pid;
            time[k++] = p[min].temp;
        }
        if (!flag)
            break;
    }
}

void gantt(process *p, int n, int size)
{
    printf("\n\n");
    for (int i = 0; i < (time[size - 1] * 2 + size - 11) / 2; i++)
        printf(" ");
    printf("GANTT CHART\n\n ");
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < time[i] - time[i - 1]; j++)
            printf("--");
        printf(" ");
    }
    printf("\n|");
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < time[i] - time[i - 1] - 1; j++)
            printf(" ");
        printf("P%d", pid[i]);
        for (j = 0; j < time[i] - time[i - 1] - 1; j++)
            printf(" ");
        printf("|");
    }
    printf("\n ");
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < time[i] - time[i - 1]; j++)
            printf("--");
        printf(" ");
    }
    printf("\n%d", p[0].arrival);
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < time[i] - time[i - 1]; j++)
            printf("  ");
        if (time[i] > 9)
            printf("\b");
        printf("%d", time[i]);
    }
    printf("\n");
}

void average(process *p, int n)
{
    float sumw = 0, sumt = 0;
    for (int i = 0; i < n; i++)
    {
        sumw += p[i].wait;
        sumt += p[i].turn;
    }
    printf("\n\nAverage Waiting Time = %0.3f", sumw / n);
    printf("\nAverage Turnaround Time = %0.3f\n", sumt / n);
}

void main()
{
    process *p;
    int n, quantum, size = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    p = (process *)malloc(sizeof(process) * n);
    printf("Enter the time quantum : ");
    scanf("%d", &quantum);
    printf("Enter the arrival time and burst time of Processes\n");
    for (int i = 0; i < n; i++)
    {
        printf("\nProcess [%d] : \nArrival time : ", i + 1);
        scanf("%d", &p[i].arrival);
        printf("Burst time : ");
        scanf("%d", &p[i].burst);
        p[i].pid = i + 1;
        p[i].temp = p[i].arrival;
        float f = p[i].burst / (float)quantum;
        size += ceil(f);
    }
    pid = (int *)malloc(sizeof(int) * size);
    time = (int *)malloc(sizeof(int) * size);
    sort_arrival_time(p, n);
    round_robin(p, n, quantum);
    printf("\n\n                       ROUND ROBIN SCHEDULING");
    printf("\n------------------------------------------------------------------------\n");
    printf("Processes   Arrival time   Burst time    Waiting time    Turnaround time\n");
    printf("------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("    P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival, p[i].burst,
               p[i].wait, p[i].turn);
    }
    printf("------------------------------------------------------------------------\n");
    gantt(p, n, size);
    average(p, n);
}