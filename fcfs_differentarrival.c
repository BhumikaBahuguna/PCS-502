#include <stdio.h>

// Structure for process
struct Process {
    int id;
    int at;   // arrival time
    int bt;   // burst time
    int ct;   // completion time
    int tat;  // turnaround time
    int wt;   // waiting time
};

// Function to sort processes by arrival time
void sortByArrival(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// Function to calculate times
void calculateTimes(struct Process p[], int n) {
    int sum = 0;

    // If first process arrives later than time 0
    if (p[0].at > 0) {
        sum = p[0].at;
    }

    for (int i = 0; i < n; i++) {
        if (sum < p[i].at) {
            sum = p[i].at;  // CPU is idle until process arrives
        }

        sum += p[i].bt;
        p[i].ct = sum;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
}

// Function to display process table and averages
void display(struct Process p[], int n) {
    float totalWT = 0, totalTAT = 0;

    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnAround\tCompletion\n");
    for (int i = 0; i < n; i++) {
        printf(" P[%d]\t   %d\t   %d\t   %d\t     %d\t\t   %d\n",
               p[i].id, p[i].at, p[i].bt, p[i].wt, p[i].tat, p[i].ct);

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
}

// Function to print Gantt chart
void printGanttChart(struct Process p[], int n) {
    printf("\nGantt Chart:\n");

    // Print process IDs
    for (int i = 0; i < n; i++) {
        printf("| P%d ", p[i].id);
    }
    printf("|\n");

    // Print timeline
    printf("0");
    for (int i = 0; i < n; i++) {
        printf("   %d", p[i].ct);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival time for P%d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &p[i].bt);
    }

    sortByArrival(p, n);
    calculateTimes(p, n);
    display(p, n);
    printGanttChart(p, n);

    return 0;
}
