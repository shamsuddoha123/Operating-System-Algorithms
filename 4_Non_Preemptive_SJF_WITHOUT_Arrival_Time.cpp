#include <iostream>
using namespace std;

int main()
{
    int n, i, j, temp;
    int pid[20], bt[20], ct[20], tat[20], wt[20], rt[20];
    float total_wt = 0, total_tat = 0, total_rt = 0;

    cout << "Enter number of processes: ";
    cin >> n;

    for (i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        cout << "Process " << i + 1 << " Burst Time: ";
        cin >> bt[i];
    }

    // Sort by BT, tie-breaker using PID
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
    ct[0] = bt[0];
    tat[0] = ct[0];
    wt[0] = tat[0] - bt[0];
    rt[0] = wt[0];

    // Remaining processes
    for (i = 1; i < n; i++)
    {
        ct[i] = ct[i - 1] + bt[i];
        tat[i] = ct[i];
        wt[i] = tat[i] - bt[i];
        rt[i] = wt[i];
    }

    // Print Table
    cout << "\nProcess\tBT\tCT\tTAT\tWT\tRT\n";
    for (i = 0; i < n; i++)
    {
        cout << "P" << pid[i] << "\t"
            << bt[i] << "\t"
            << ct[i] << "\t"
            << tat[i] << "\t"
            << wt[i] << "\t"
            << rt[i] << endl;

        total_wt += wt[i];
        total_tat += tat[i];
        total_rt += rt[i];
    }

    cout << "\nAverage Waiting Time: " << total_wt / n;
    cout << "\nAverage Turnaround Time: " << total_tat / n;
    cout << "\nAverage Response Time: " << total_rt / n << endl;

    return 0;
}