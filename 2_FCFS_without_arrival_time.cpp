#include <iostream>
using namespace std;

int main()
{
    int n, i;
    int bt[20], wt[20], ct[20], tat[20], rt[20];
    float total_wt = 0, total_tat = 0, total_rt = 0;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter burst time for each process:\n";
    for (i = 0; i < n; i++)
    {
        cout << "Process " << i + 1 << ": ";
        cin >> bt[i];
    }

    // First process
    ct[0] = bt[0];          // Completion Time
    tat[0] = ct[0];         // Turnaround Time
    wt[0] = tat[0] - bt[0]; // Waiting Time
    rt[0] = wt[0];          // Response Time

    // Remaining processes
    for (i = 1; i < n; i++)
    {
        ct[i] = ct[i - 1] + bt[i]; // Completion Time
        tat[i] = ct[i];            // Turnaround Time
        wt[i] = tat[i] - bt[i];    // Waiting Time
        rt[i] = wt[i];             // Response Time
    }

    // Print table and calculate average
    cout << "\nProcess\tBT\tCT\tTAT\tWT\tRT\n";
    for (i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << "\t"
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