#include <stdio.h>

int main() {
    int n, r;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &r);

    int alloc[n][r], max[n][r], need[n][r], avail[r];
    int f[n], ans[n], ind = 0;

    printf("\nEnter Allocation Matrix (%d x %d):\n", n, r);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nEnter Maximum Matrix (%d x %d):\n", n, r);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter Available Resources (%d):\n", r);
    for (int i = 0; i < r; i++) {
        scanf("%d", &avail[i]);
    }

    // Calculate Need matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Display all matrices
    printf("\nAllocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            printf("%3d ", alloc[i][j]);
        }
        printf("\n");
    }

    printf("\nMaximum Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            printf("%3d ", max[i][j]);
        }
        printf("\n");
    }

    printf("\nNeed Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            printf("%3d ", need[i][j]);
        }
        printf("\n");
    }

    printf("\nAvailable Resources:\n");
    for (int i = 0; i < r; i++) {
        printf("%3d ", avail[i]);
    }
    printf("\n");

    // Initialize finish flags
    for (int k = 0; k < n; k++) {
        f[k] = 0;
    }

    int count = 0;
    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (int j = 0; j < r; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {
                    for (int y = 0; y < r; y++)
                        avail[y] += alloc[i][y];
                    ans[ind++] = i;
                    f[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }

        if (!found) {
            printf("\nSystem is NOT in a safe state!\n");
            return 0;
        }
    }

    printf("\nSystem is in a SAFE state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++) {
        printf("P%d", ans[i]);
        if (i != n - 1)
            printf(" -> ");
    }
    printf("\n");

    return 0;
}