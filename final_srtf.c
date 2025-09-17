#include <stdio.h>
#include <limits.h>

int main() {
    int n, i;
    int at[20], bt[20], rt[20], ct[20], tat[20], wt[20];
    int time = 0, comp = 0;
    int sumtat = 0, sumwt = 0;
    int order[100], endtime[100], k = 0; // for Gantt chart

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];  // remaining time
    }

    int prev = -1; // track last executed process

    while (comp < n) {
        int idx = -1, minrt = INT_MAX;

        // find process with shortest remaining time among arrived
        for (i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0 && rt[i] < minrt) {
                minrt = rt[i];
                idx = i;
            }
        }

        if (idx == -1) {  // no process available
            time++;
            continue;
        }

        // if new process selected (context switch), record Gantt chart
        if (idx != prev) {
            order[k] = idx;
            endtime[k] = time;
            k++;
        }

        // execute for 1 unit
        rt[idx]--;
        time++;

        if (rt[idx] == 0) {   // completed
            comp++;
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            sumtat += tat[idx];
            sumwt += wt[idx];
        }

        prev = idx;
    }

    // Final endtime for last process
    endtime[k] = time;

    // Output
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", (float)sumtat / n);
    printf("\nAverage Waiting Time = %.2f\n", (float)sumwt / n);

    // Gantt Chart
    printf("\nGantt Chart:\n ");
    for (i = 0; i < k; i++) {
        printf("|  P%d  ", order[i] + 1);
    }
    printf("|\n");
    for (i = 0; i <= k; i++) {
        printf("%-6d", endtime[i]);
    }
    printf("\n");

    return 0;
}
