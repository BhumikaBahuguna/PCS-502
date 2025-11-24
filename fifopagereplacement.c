//FIFO
#include <stdio.h>
int main() {
    int i, j, n, f, index = 0;
    int pages[50], frames[10];
    int pageFaults = 0, hits = 0;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    printf("Enter number of frames: ");
    scanf("%d", &f);
    for (i = 0; i < f; i++) {
        frames[i] = -1;
    }
    printf("\nPage Reference String -> Frame Contents\n");
    for (i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;
        for (j = 0; j < f; j++) {
            if (frames[j] == page) {
                found = 1;
                hits++;
                break;
            }
        }
        if (!found) {
            frames[index] = page;
            index = (index + 1) % f;
            pageFaults++;
        }
        printf("%d -> ", page);
        for (j = 0; j < f; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    int misses = pageFaults;
    printf("\nTotal Hits = %d\n", hits);
    printf("Total Misses = %d\n", misses);
    return 0;
}
