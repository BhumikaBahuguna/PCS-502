#include <stdio.h>
#include <limits.h>

int main() {
    int n, i, j;
    int at[20], bt[20], ct[20], tat[20], wt[20], done[20];
    int time = 0, comp = 0;
    int sumtat = 0, sumwt = 0;
    int order[20], endtime[20], k = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        done[i] = 0;
    }

    while (comp < n) {
        int idx = -1, minbt = INT_MAX;

        // find shortest available job
        for (i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time && bt[i] < minbt) {
                minbt = bt[i];
                idx = i;
            }
        }

        if (idx == -1) {  // no process has arrived yet
            time++;
            continue;
        }

        time += bt[idx];
        ct[idx] = time;
        tat[idx] = ct[idx] - at[idx];
        wt[idx] = tat[idx] - bt[idx];

        sumtat += tat[idx];
        sumwt += wt[idx];

        done[idx] = 1;
        comp++;

        // ✅ store for Gantt chart
        order[k] = idx + 1;   // process number (P1, P2,...)
        endtime[k] = time;    // when it finished
        k++;
    }

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
        printf("|  P%d  ", order[i]);
    }
    printf("|\n");

    printf("0");
    for (i = 0; i < k; i++) {
        printf("     %d", endtime[i]);
    }
    printf("\n");

    return 0;
}
