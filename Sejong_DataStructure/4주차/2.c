#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

    int n, k, i;
    int x[100];
    int info[100];
    int bef, aft;

    scanf("%d", &n);

    for (i = 0; i < n; i++)
        scanf("%d", &x[i]);

    scanf("%d", &k);

    for (i = 0; i < k; i++)
        scanf("%d", &info[i]);

    bef = x[info[0]];

    for (i = 1; i < k; i++) {

        aft = x[info[i]];

        x[info[i]] = bef;

        bef = aft;
    }

    for (i = 0; i < n; i++)
        printf(" %d", x[i]);

    return 0;
}