#include <stdio.h>

int main()
{
    int n, i;
    int bt[20], wt[20], ct[20], tat[20], rt[20];
    float total_wt = 0, total_tat = 0, total_rt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++)
    {
        printf("Process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // First process
    wt[0] = 0;
    ct[0] = bt[0];
    tat[0] = ct[0];
    rt[0] = wt[0];

    // Remaining processes
    for (i = 1; i < n; i++)
    {
        ct[i] = ct[i - 1] + bt[i];
        tat[i] = ct[i];
        wt[i] = wt[i - 1] + bt[i - 1];
        rt[i] = wt[i];
    }

    printf("\nProcess\tBT\tWT\tCT\tTAT\tRT\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
            i + 1, bt[i], wt[i], ct[i], tat[i], rt[i]);

        total_wt += wt[i];
        total_tat += tat[i];
        total_rt += rt[i];
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Response Time: %.2f\n", total_rt / n);

    return 0;
}
