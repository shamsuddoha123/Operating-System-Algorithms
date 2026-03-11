#include <stdio.h>

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[20], at[20], bt[20], ct[20], tat[20], wt[20], rt[20];
    int remaining_bt[20];
    int is_completed[20] = {0};
    int is_started[20] = {0};

    float total_wt = 0, total_tat = 0, total_rt = 0;

    // Input
    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        printf("Process %d Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);

        remaining_bt[i] = bt[i];
    }

    int completed = 0;
    int current_time = 0;

    while (completed < n)
    {
        int idx = -1;
        int min_rt = 1000000000;

        // Select process with shortest remaining time
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= current_time && is_completed[i] == 0)
            {
                if (remaining_bt[i] < min_rt)
                {
                    min_rt = remaining_bt[i];
                    idx = i;
                }
            }
        }

        // CPU idle
        if (idx == -1)
        {
            current_time++;
        }
        else
        {
            // First time execution → Response Time
            if (is_started[idx] == 0)
            {
                rt[idx] = current_time - at[idx];
                is_started[idx] = 1;
            }

            // Execute for 1 unit (preemptive)
            remaining_bt[idx]--;
            current_time++;

            // If process finishes
            if (remaining_bt[idx] == 0)
            {
                ct[idx] = current_time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];

                total_wt += wt[idx];
                total_tat += tat[idx];
                total_rt += rt[idx];

                is_completed[idx] = 1;
                completed++;
            }
        }
    }

    // Output
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            pid[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Response Time: %.2f\n", total_rt / n);

    return 0;
}