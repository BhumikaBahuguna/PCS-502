#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], pr[n], ct[n], tat[n], wt[n], done[n];
    int order[n], st[n]; // For Gantt chart
    int time = 0, completed = 0;
    float sum_tat = 0, sum_wt = 0;

    printf("Enter Arrival Time, Burst Time and Priority of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        printf("P%d Priority (lower value = higher priority): ", i + 1);
        scanf("%d", &pr[i]);
        done[i] = 0;
    }

    while (completed < n) {
        int idx = -1, bestPriority = INT_MAX;

        // Select process: by priority → arrival time → process ID
        for (int i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time) {
                if (idx == -1 || pr[i] < bestPriority ||
                    (pr[i] == bestPriority && at[i] < at[idx]) ||
                    (pr[i] == bestPriority && at[i] == at[idx] && i < idx)) {
                    bestPriority = pr[i];
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++; // No process ready yet
            continue;
        }

        st[completed] = time;      // Record start time for Gantt chart
        order[completed] = idx;    // Execution order
        time += bt[idx];           // Execute
        ct[idx] = time;
        tat[idx] = ct[idx] - at[idx];
        wt[idx] = tat[idx] - bt[idx];
        sum_tat += tat[idx];
        sum_wt += wt[idx];
        done[idx] = 1;
        completed++;
    }

    // Results
    printf("\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", sum_tat / n);
    printf("\nAverage Waiting Time = %.2f\n", sum_wt / n);

    // Gantt Chart
    printf("\nGantt Chart:\n ");
    for (int i = 0; i < n; i++) {
        printf("|  P%d  ", order[i] + 1);
    }
    printf("|\n");

    printf("%d", st[0]);
    for (int i = 0; i < n; i++) {
        printf("     %d", ct[order[i]]);
    }
    printf("\n");

    return 0;
}
