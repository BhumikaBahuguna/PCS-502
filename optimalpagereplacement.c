//OPR
#include <stdio.h>
int search(int key, int fr[], int fn) {
    for (int i = 0; i < fn; i++) {
        if (fr[i] == key)
            return 1;
    }
    return 0;
}
int predict(int pg[], int fr[], int pn, int fn, int index) {
    int res = -1, farthest = index;
    for (int i = 0; i < fn; i++) {
        int j;
        for (j = index; j < pn; j++) {
            if (fr[i] == pg[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == pn)
            return i;
    }
    return (res == -1) ? 0 : res;
}
void optimalPage(int pg[], int pn, int fn) {
    int fr[50];
    int hit = 0;
    int filled = 0;
    for (int i = 0; i < fn; i++)
        fr[i] = -1;
    for (int i = 0; i < pn; i++) {
        if (search(pg[i], fr, fn)) {
            hit++;
            continue;
        }
        if (filled < fn) {
            fr[filled++] = pg[i];
        } 
        else {
            int pos = predict(pg, fr, pn, fn, i + 1);
            fr[pos] = pg[i];
        }
    }
    printf("\nTotal Hits = %d\n", hit);
    printf("Total Misses = %d\n", pn - hit);
}
int main() {
    int fn, pn;
    printf("Enter number of frames: ");
    scanf("%d", &fn);
    printf("Enter number of pages: ");
    scanf("%d", &pn);
    int pg[pn];
    printf("Enter reference string (%d pages): ", pn);
    for (int i = 0; i < pn; i++) {
        scanf("%d", &pg[i]);
    }
    optimalPage(pg, pn, fn);
    return 0;
}
