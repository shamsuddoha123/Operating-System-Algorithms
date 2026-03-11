#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int pid[20], at[20], bt[20], ct[20], tat[20], wt[20], rt[20];
    bool is_completed[20] = {0};
    float total_wt = 0, total_tat = 0, total_rt = 0;

    // Input
    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        cout << "Process " << i + 1 << " Arrival Time: ";
        cin >> at[i];
        cout << "Process " << i + 1 << " Burst Time: ";
        cin >> bt[i];
    }

    int completed = 0;
    int current_time = 0;

    while (completed < n)
    {
        int idx = -1;
        int min_bt = 1e9;

        // Select process with shortest BT among arrived ones
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= current_time && !is_completed[i])
            {
                // Tie-breaker: choose earliest arrival if BT same
                if (bt[i] < min_bt || (bt[i] == min_bt && at[i] < at[idx]))
                {
                    min_bt = bt[i];
                    idx = i;
                }
            }
        }

        if (idx == -1)
        {
            // CPU idle
            current_time++;
        }
        else
        {
            rt[idx] = current_time - at[idx];  // Response Time
            current_time += bt[idx];           // Execute
            ct[idx] = current_time;            // Completion Time
            tat[idx] = ct[idx] - at[idx];      // Turnaround Time
            wt[idx] = tat[idx] - bt[idx];      // Waiting Time

            total_wt += wt[idx];
            total_tat += tat[idx];
            total_rt += rt[idx];

            is_completed[idx] = true;
            completed++;
        }
    }

    // Output Table
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << pid[i] << "\t"
            << at[i] << "\t"
            << bt[i] << "\t"
            << ct[i] << "\t"
            << tat[i] << "\t"
            << wt[i] << "\t"
            << rt[i] << endl;
    }

    cout << "\nAverage Waiting Time: " << total_wt / n;
    cout << "\nAverage Turnaround Time: " << total_tat / n;
    cout << "\nAverage Response Time: " << total_rt / n << endl;

    return 0;
}