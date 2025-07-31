#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main() {
    int start, end;
    printf("Enter start: ");
    scanf("%d", &start);
    printf("Enter end: ");
    scanf("%d", &end);
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        int oddsum = 0;
        for (int i = start; i <= end; i++) {
            if (i % 2 != 0) {
                oddsum += i;
            }
        }
        printf("Child Process (PID: %d): Sum of odd numbers = %d\n", getpid(), oddsum);
    } else {
        int evensum=0;
        for (int i = start; i <= end; i++) {
            if (i % 2 == 0) {
                evensum += i;
            }
        }
        printf("Parent Process (PID: %d): Sum of even numbers = %d\n", getpid(), evensum);
    }

    return 0;
}
