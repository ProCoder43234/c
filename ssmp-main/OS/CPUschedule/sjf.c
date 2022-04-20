#include <stdio.h>
#include <stdlib.h>

typedef struct process
{
    int pid, arrival, burst, wait, turn;
} process;

void sort_arrival_time(process *p, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (p[min].arrival > p[j].arrival)
            {
                min = j;
            }
        }
        if (i != min)
        {
            process temp = p[i];
            p[i] = p[min];
            p[min] = temp;
        }
    }
}

void sjfs(process *p, int n)
{
    int previous = p[0].arrival;
    for (int i = 0; i < n; i++)
    {
        int min = p[i].burst;
        int min_index = i;
        int flag = 0;
        for (int j = i + 1; j < n; j++)
        {
            if (p[j].arrival > previous)
                break;
            if (p[j].burst < min)
            {
                min = p[j].burst;
                min_index = j;
                flag = 1;
            }
        }
        if (flag == 1)
        {
            process temp = p[i];
            p[i] = p[min_index];
            p[min_index] = temp;
        }
        p[i].wait = previous - p[i].arrival;
        if (p[i].wait < 0)
            p[i].wait = 0;
        p[i].turn = p[i].burst + p[i].wait;
        previous = p[i].arrival + p[i].turn;
    }
}

void gantt_chart(process *p, int n)
{
    printf("\n\n");
    for (int i = 0; i < p[n - 1].turn - 1; i++)
    {
        printf(" ");
    }
    printf("GANTT CHART\n\n ");

    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].burst; j++)
            printf("--");
        printf(" ");
    }
    printf("\n|");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].burst - 1; j++)
            printf(" ");
        printf("P%d", p[i].pid);
        for (j = 0; j < p[i].burst - 1; j++)
            printf(" ");
        printf("|");
    }
    printf("\n ");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].burst; j++)
            printf("--");
        printf(" ");
    }
    printf("\n%d", p[0].arrival);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].burst; j++)
            printf("  ");
        if (p[i].turn + p[i].arrival > 9)
            printf("\b");
        printf("%d", p[i].turn + p[i].arrival);
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
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    process *p = (process *)malloc(sizeof(process) * n);
    printf("Enter the arrival time and burst time of Processes\n");
    for (int i = 0; i < n; i++)
    {
        printf("\nProcess [%d] : \nArrival time : ", i + 1);
        scanf("%d", &p[i].arrival);
        printf("Burst time : ");
        scanf("%d", &p[i].burst);
        p[i].pid = i + 1;
    }
    sort_arrival_time(p, n);
    sjfs(p, n);
    printf("\n\n                   SHORTEST JOB FIRST SCHEDULING");
    printf("\n------------------------------------------------------------------------\n");
    printf("Processes   Arrival time   Burst time    Waiting time    Turnaround time\n");
    printf("------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("    P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival, p[i].burst,
               p[i].wait, p[i].turn);
    }
    printf("------------------------------------------------------------------------\n");
    gantt_chart(p, n);
    average(p, n);
}