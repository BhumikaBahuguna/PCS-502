#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rbt[n], pr[n], ct[n], tat[n], wt[n];
    int time = 0, completed = 0;
    float sum_tat = 0, sum_wt = 0;

    // For Gantt chart
    int gantt_process[1000], gantt_time[1000], gcnt = 0;

    printf("Enter Arrival Time, Burst Time and Priority of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d Arrival Time: ", i+1);
        scanf("%d", &at[i]);
        printf("P%d Burst Time: ", i+1);
        scanf("%d", &bt[i]);
        printf("P%d Priority (lower value = higher priority): ", i+1);
        scanf("%d", &pr[i]);
        rbt[i] = bt[i];  // Remaining burst time
    }

    while (completed < n) {
        int idx = -1, bestPriority = INT_MAX;

        // Find process with highest priority among arrived
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rbt[i] > 0) {
                if (pr[i] < bestPriority || 
                   (pr[i] == bestPriority && at[i] < at[idx]) || 
                   (pr[i] == bestPriority && at[i] == at[idx] && i < idx)) {
                    bestPriority = pr[i];
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;  // No process available yet
            continue;
        }

        // Record for Gantt Chart (only when process changes)
        if (gcnt == 0 || gantt_process[gcnt-1] != idx) {
            gantt_process[gcnt] = idx;
            gantt_time[gcnt] = time;
            gcnt++;
        }

        // Run the process for 1 unit
        rbt[idx]--;
        time++;

        // If process completes
        if (rbt[idx] == 0) {
            completed++;
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            sum_tat += tat[idx];
            sum_wt += wt[idx];
        }
    }

    // Output
    printf("\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", sum_tat / n);
    printf("\nAverage Waiting Time = %.2f\n", sum_wt / n);

    // Gantt Chart
    printf("\nGantt Chart:\n ");
    for (int i = 0; i < gcnt; i++) {
        printf("|  P%d  ", gantt_process[i] + 1);
    }
    printf("|\n");

    printf("%d", gantt_time[0]);
    for (int i = 0; i < gcnt; i++) {
        printf("     %d", (i + 1 < gcnt) ? gantt_time[i+1] : ct[gantt_process[i]]);
    }
    printf("\n");

    return 0;
}
