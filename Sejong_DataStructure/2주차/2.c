#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int mostOnes(int A[100][100], int n) {

    int i = 0, j = 0, row = 0;

    while (i < n && j < n) {
        if (A[i][j] == 1) {
            row = i;
            j += 1;
        }
        else {
            i += 1;
        }
    }

    return row;
}

int main(void)
{
    int n;
    int A[100][100];
    int i, j, result;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    result = mostOnes(A, n);

    printf("%d", result);

    return 0;
}