#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

    int n;
    int i, j, k = 1;
    int x[100][100];

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        if (i % 2 == 0) {
            for (j = 0; j < n; j++)
                x[i][j] = k++;
        }
        else {
            for (j = n - 1; j >= 0; j--)
                x[i][j] = k++;
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf(" %d", x[i][j]);
        printf("\n");
    }

    return 0;
}