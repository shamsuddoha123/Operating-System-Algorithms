#include <stdio.h>

int main()
{
    int n, tq;
    int pid[20], bt[20], ct[20], tat[20], wt[20], rt[20];
    int rem[20];
    int rq[50];
    int front = 0, rear = 0;
    int current_time = 0, completed = 0;

    float total_wt = 0, total_tat = 0, total_rt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        rem[i] = bt[i];
        rt[i] = -1;   // Response time not yet set
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    /* Add all processes to ready queue initially */
    for (int i = 0; i < n; i++)
        rq[rear++] = i;

    while (completed < n)
    {
        int i = rq[front++];

        if (rt[i] == -1)
            rt[i] = current_time;   // AT = 0

        if (rem[i] > tq) // Process will not finish in this quantum
        {
            current_time += tq;
            rem[i] -= tq;
        }
        else
        {
            current_time += rem[i];
            rem[i] = 0;
            ct[i] = current_time;
            tat[i] = ct[i];         // AT = 0
            wt[i] = tat[i] - bt[i];

            total_wt += wt[i];
            total_tat += tat[i];
            total_rt += rt[i];

            completed++;
        }

        if (rem[i] > 0) // If process is not yet complete, re-add to queue
            rq[rear++] = i;
    }

    printf("\nProcess\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
            pid[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Response Time: %.2f\n", total_rt / n);

    return 0;
}