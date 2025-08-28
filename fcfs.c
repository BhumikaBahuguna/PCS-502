#include <stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[]) {
    wt[0] = 0;
    for (int i = 1; i < n; i++)
        wt[i] = bt[i - 1] + wt[i - 1];
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

void findavgTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    int total_wt = 0, total_tat = 0;

    findWaitingTime(processes, n, bt, wt);
    findTurnAroundTime(processes, n, bt, wt, tat);

    printf("Processes   Burst time   Waiting time   Turn around time\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("   %d         %d           %d              %d\n", processes[i], bt[i], wt[i], tat[i]);
    }

    printf("Average waiting time = %.2f\n", (float)total_wt / n);
    printf("Average turn around time = %.2f\n", (float)total_tat / n);
}

void printGanttChart(int processes[], int n, int bt[], int wt[]) {
    printf("\nGantt Chart:\n ");

    for (int i = 0; i < n; i++) {
        printf("---------");
    }
    printf("\n|");

    for (int i = 0; i < n; i++) {
        printf("   P%d   |", processes[i]);
    }
    printf("\n ");

    for (int i = 0; i < n; i++) {
        printf("---------");
    }
    printf("\n");

    printf("0");
    for (int i = 0; i < n; i++) {
        printf("        %d", wt[i] + bt[i]);
    }
    printf("\n\n");
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int processes[n], bt[n], wt[n], tat[n];

    for (int i = 0; i < n; i++) {
        printf("Enter process id for process %d: ", i + 1);
        scanf("%d", &processes[i]);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    findavgTime(processes, n, bt, wt, tat);
    printGanttChart(processes, n, bt, wt);

    return 0;
}

