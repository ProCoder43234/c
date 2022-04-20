#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct process
{
    int arrival_time;
    int burst_time;
    int bt_tracker;
    int processTypeBit;
} process;

int prevIndex = -1;
int findSystemProcess(process *Process, int count, int time)
{
    int startIndex = (prevIndex + 1) % count;
    int systemIndex = -1;
    for (int i = startIndex; i < count; ++i)
        if (Process[i].bt_tracker > 0 && Process[i].arrival_time <= time && Process[i].processTypeBit == 0)
        {
            systemIndex = prevIndex = i;
            break;
        }

    if (systemIndex == -1)
        for (int i = 0; i < startIndex; ++i)
            if (Process[i].bt_tracker > 0 && Process[i].arrival_time <= time && Process[i].processTypeBit == 0)
            {
                systemIndex = prevIndex = i;
                break;
            }

    return systemIndex;
}

void printGantt(int ganttVal[], int valIndex, int ganttTime[], int timeIndex)
{
    int i;
    printf("\nGantt Chart\n ");
    for (i = 0; i < valIndex; ++i)
        printf("--------");
    printf("\n|");
    for (i = 0; i < valIndex; ++i)
    {
        if (ganttVal[i] == -1)
            printf("     \t |");
        else
            printf("   P%d\t |", ganttVal[i]);
    }
    printf("\n ");
    for (i = 0; i < valIndex; ++i)
        printf("--------");
    printf("\n0\t");
    for (i = 0; i < timeIndex; ++i)
        printf(" %d\t", ganttTime[i]);
    printf("\n");
}

void main()
{
    int i, n, quant, wt = 0, tat = 0;
    float avg_wt, avg_tat;

    int ganttVal[100], valIndex = 0, timeIndex = 0, ganttTime[100];

    printf("Enter the total number of processes in the system: ");
    scanf("%d", &n);

    process *Process = (process *)malloc(sizeof(process) * n);

    for (i = 0; i < n; ++i)
    {
        printf("\nProcess[%d]", i + 1);
        printf("\nEnter arrival time: ");
        scanf("%d", &Process[i].arrival_time);
        printf("Enter burst time: ");
        scanf("%d", &Process[i].burst_time);
        printf("System/User process (0/1): ");
        scanf("%d", &Process[i].processTypeBit);
        Process[i].bt_tracker = Process[i].burst_time;
    }

    printf("\nEnter the time quantum for the process: ");
    scanf("%d", &quant);

    printf("\nProcess ID \t\t System/User \t\t Burst Time \t\t Turn around time \t\t Waiting Time");
    printf("\n---------- \t\t ----------- \t\t ---------- \t\t ---------------- \t\t ------------");

    i = 0;
    int sum = 0, completed = 0, t_time, w_time, systemIndex;

    while (completed != n)
    {
        systemIndex = findSystemProcess(Process, n, sum);

        if (systemIndex != -1)
            i = systemIndex;

        if (Process[i].bt_tracker > 0 && Process[i].arrival_time <= sum)
        {
            if (Process[i].arrival_time > sum)
            {
                ganttVal[valIndex++] = -1;
                ganttTime[timeIndex++] = Process[i].arrival_time;
                sum = Process[i].arrival_time;
            }

            if (Process[i].bt_tracker <= quant)
            {
                sum += Process[i].bt_tracker;
                Process[i].bt_tracker = 0;
                completed++;

                t_time = sum - Process[i].arrival_time;
                w_time = t_time - Process[i].burst_time;
                tat += t_time;
                wt += w_time;

                char type[10];
                if (Process[i].processTypeBit == 0)
                    strcpy(type, "System");
                else
                    strcpy(type, "User  ");
                printf("\nProcess[%d] \t\t %s \t\t %d \t\t\t %d \t\t\t\t %d", i + 1, type, Process[i].burst_time, t_time, w_time);
            }
            else
            {
                Process[i].bt_tracker -= quant;
                sum += quant;
            }

            ganttVal[valIndex++] = i + 1;
            ganttTime[timeIndex++] = sum;
        }

        if (i == n - 1)
            i = 0;

        else
            ++i;
    }

    avg_wt = wt * 1.0 / n;
    avg_tat = tat * 1.0 / n;

    printf("\n\nAverage Turn Around Time: %f", avg_tat);
    printf("\nAverage Waiting Time: %f\n", avg_wt);

    printGantt(ganttVal, valIndex, ganttTime, timeIndex);
}