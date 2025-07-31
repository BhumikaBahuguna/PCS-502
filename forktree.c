#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid1, pid2;

    printf("Root process started. PID = %d\n", getpid());

    pid1 = fork();
    if (pid1 < 0) {
        perror("fork 1 failed");
        exit(1);
    }

    if (pid1 == 0) {
        // This is child 1
        printf("Child 1: PID = %d, Parent PID = %d\n", getpid(), getppid());

        pid2 = fork();
        if (pid2 < 0) {
            perror("fork 2 failed (in child 1)");
            exit(1);
        }

        if (pid2 == 0) {
            // Grandchild process
            printf("Grandchild (child of child 1): PID = %d, Parent PID = %d\n", getpid(), getppid());
        }

    } else {
        // This is the parent
        pid2 = fork();
        if (pid2 < 0) {
            perror("fork 2 failed (in parent)");
            exit(1);
        }

        if (pid2 == 0) {
            // This is child 2
            printf("Child 2: PID = %d, Parent PID = %d\n", getpid(), getppid());
        }
    }

    return 0;
}
