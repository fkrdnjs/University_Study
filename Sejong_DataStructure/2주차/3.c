/* 3-1번 입니다. ------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int* prefixAverages1(int* X, int n) {

    int i, j, sum;
    int* A;

    A = (int*)malloc(sizeof(int) * n);
    if (A == NULL)
        return -1;

    for (i = 0; i < n; i++) {
        sum = 0;
        for (j = 0; j <= i; j++) {
            sum += X[j];
        }
        A[i] = (int)((double)sum / (double)(i + 1) + 0.5);
    }

    return A;
}

int* prefixAverages2(int* X, int n) {

    int i, sum = 0;
    int* A;

    A = (int*)malloc(sizeof(int) * n);
    if (A == NULL)
        return -1;

    for (i = 0; i < n; i++) {
        sum += X[i];
        A[i] = (int)((double)sum / (double)(i + 1) + 0.5);
    }

    return A;
}

int main(void)
{
    int n, i;
    int* X;
    int* A1, * A2;

    scanf("%d", &n);

    X = (int*)malloc(sizeof(int) * n);
    if (X == NULL)
        return -1;

    for (i = 0; i < n; i++)
        scanf("%d", &X[i]);

    A1 = prefixAverages1(X, n);

    for (i = 0; i < n; i++)
        printf("%d ", A1[i]);

    printf("\n");

    A2 = prefixAverages2(X, n);

    for (i = 0; i < n; i++)
        printf("%d ", A2[i]);

    free(A2);
    free(A1);
    free(X);

    return 0;
}


/* 3-2번 입니다 ---------------------------------------------

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int *prefixAverages1(int* X, int n) {

    int i, j, sum;
    int* A;

    A = (int*)malloc(sizeof(int) * n);
    if (A == NULL)
        return -1;

    for (i = 0; i < n; i++) {
        sum = 0;
        for (j = 0; j <= i; j++) {
            sum += X[j];
        }

        A[i] = (int)((double)sum / (double)(i + 1) + 0.5);

    }

    return A;
}

int* prefixAverages2(int* X, int n) {

    int i, sum = 0;
    int* A;

    A = (int*)malloc(sizeof(int) * n);
    if (A == NULL)
        return -1;

    for (i = 0; i < n; i++) {
        sum += X[i];
        A[i] = (int)((double)sum / (double)(i + 1) + 0.5);

    }

    return A;
}

int main(void)
{
    int n, i;
    int* X;
    int* A1, * A2;
    LARGE_INTEGER ticks;
    LARGE_INTEGER start, end, diff;
    LARGE_INTEGER start2, end2, diff2;

    scanf("%d", &n);

    X = (int*)malloc(sizeof(int) * n);
    if (X == NULL)
        return -1;

    srand(time(NULL));

    for (i = 0; i < n; i++) {
        X[i] = rand() % 10000 + 1;
    }

    QueryPerformanceFrequency(&ticks);

    QueryPerformanceCounter(&start);
    A1 = prefixAverages1(X, n);
    QueryPerformanceCounter(&end);

    diff.QuadPart = end.QuadPart - start.QuadPart;

    printf("%.9lfms\n", (double)diff.QuadPart / (double)ticks.QuadPart);

    QueryPerformanceCounter(&start2);
    A2 = prefixAverages2(X, n);
    QueryPerformanceCounter(&end2);

    diff2.QuadPart = end2.QuadPart - start2.QuadPart;

    printf("%.9lfms", (double)diff2.QuadPart / (double)ticks.QuadPart);

    free(A2);
    free(A1);
    free(X);

    return 0;
}

*/
