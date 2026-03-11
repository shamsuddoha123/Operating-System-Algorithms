#include <stdio.h>

int main()
{
    int n, i, j, temp;
    int pid[20], bt[20], ct[20], tat[20], wt[20], rt[20];
    float total_wt = 0, total_tat = 0, total_rt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // Sort by Burst Time, tie-breaker using PID
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (bt[i] > bt[j] || (bt[i] == bt[j] && pid[i] > pid[j]))
            {
                // swap BT
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                // swap PID
                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }

    // First process
    ct[0] = bt[0];              // Completion Time
    tat[0] = ct[0];             // Turnaround Time
    wt[0] = tat[0] - bt[0];     // Waiting Time
    rt[0] = wt[0];              // Response Time

    // Remaining processes
    for (i = 1; i < n; i++)
    {
        ct[i] = ct[i - 1] + bt[i];
        tat[i] = ct[i];
        wt[i] = tat[i] - bt[i];
        rt[i] = wt[i];
    }

    // Output table
    printf("\nProcess\tBT\tCT\tTAT\tWT\tRT\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
            pid[i], bt[i], ct[i], tat[i], wt[i], rt[i]);

        total_wt += wt[i];
        total_tat += tat[i];
        total_rt += rt[i];
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Response Time: %.2f\n", total_rt / n);

    return 0;
}