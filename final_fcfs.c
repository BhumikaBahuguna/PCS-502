#include <stdio.h>

int main() {
    int n, i, j;
    int at[20], bt[20], ct[20], tat[20], wt[20], pid[20];
    int sumtat = 0, sumwt = 0, temp;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (i = 0; i < n; i++) {
        pid[i] = i + 1; // keep original process IDs
        printf("P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }

    // Sort processes by Arrival Time
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {
                temp = at[i]; at[i] = at[j]; at[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = pid[i]; pid[i] = pid[j]; pid[j] = temp; // swap process IDs too
            }
        }
    }

    // Completion Time
    ct[0] = at[0] + bt[0];
    for (i = 1; i < n; i++) {
        if (at[i] > ct[i - 1])
            ct[i] = at[i] + bt[i];
        else
            ct[i] = ct[i - 1] + bt[i];
    }

    // Turnaround Time and Waiting Time
    for (i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        sumtat += tat[i];
        sumwt += wt[i];
    }

    // Output Table
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", (float)sumtat / n);
    printf("\nAverage Waiting Time = %.2f\n", (float)sumwt / n);

    // Gantt Chart
    printf("\nGantt Chart:\n ");
    for (i = 0; i < n; i++) {
        printf("|  P%d  ", pid[i]);
    }
    printf("|\n");

    // Print timeline
    printf("0");
    for (i = 0; i < n; i++) {
        printf("     %d", ct[i]);
    }
    printf("\n");

    return 0;
}
