#include <stdio.h>

int n, m;
int wfg[20][20];
int visited[20], inStack[20];

int dfs(int u) {
    visited[u] = 1;
    inStack[u] = 1;

    for (int v = 0; v < n; v++) {
        if (wfg[u][v]) {
            if (!visited[v] && dfs(v)) return 1;
            if (inStack[v]) return 1; // back edge => cycle
        }
    }

    inStack[u] = 0;
    return 0;
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources (single instance each): ");
    scanf("%d", &m);

    int alloc[20][20], req[20][20];
    int holder[20];

    printf("Enter Allocation matrix (%d x %d) (0/1):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Request matrix (%d x %d) (0/1):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &req[i][j]);

    // Find resource holders
    for (int r = 0; r < m; r++) {
        holder[r] = -1;
        for (int p = 0; p < n; p++) {
            if (alloc[p][r] == 1) { holder[r] = p; break; }
        }
    }

    // Build WFG
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            wfg[i][j] = 0;

    for (int i = 0; i < n; i++) {
        for (int r = 0; r < m; r++) {
            if (req[i][r] == 1 && holder[r] != -1 && holder[r] != i) {
                wfg[i][holder[r]] = 1;
            }
        }
    }

    // Detect cycle
    for (int i = 0; i < n; i++) visited[i] = inStack[i] = 0;

    int deadlock = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && dfs(i)) {
            deadlock = 1;
            break;
        }
    }

    if (!deadlock) printf("\nNo Deadlock (No cycle in Wait-For Graph).\n");
    else printf("\nDeadlock Detected! (Cycle exists in Wait-For Graph)\n");

    return 0;
}
