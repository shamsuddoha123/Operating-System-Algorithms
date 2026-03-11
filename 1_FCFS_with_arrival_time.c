#include <stdio.h>

int main()
{
    int n, i, j, temp;
    int pid[20], at[20], bt[20], ct[20], tat[20], wt[20], rt[20];
    int current_time = 0, st;
    float total_wt = 0, total_tat = 0, total_rt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter arrival time and burst time for each process:\n");
    for (i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        printf("Process %d - Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("Process %d - Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // --- Sort processes by arrival time ---
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (at[i] > at[j])
            {
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
                
                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }

    // --- Calculate CT, TAT, WT, RT ---
    current_time = 0;
    for (i = 0; i < n; i++)
    {
        if (current_time < at[i])
            current_time = at[i];// Cpu becomes idle till the arrival of next process, so we update current_time

        st = current_time;  // Start Time
        rt[i] = st - at[i]; // Response Time

        ct[i] = st + bt[i]; // Completion Time
        current_time = ct[i];

        tat[i] = ct[i] - at[i]; // Turnaround Time
        wt[i] = tat[i] - bt[i]; // Waiting Time

        total_wt += wt[i];
        total_tat += tat[i];
        total_rt += rt[i];
    }

    // --- Print results ---
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            pid[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Response Time: %.2f\n", total_rt / n);

    return 0;
}