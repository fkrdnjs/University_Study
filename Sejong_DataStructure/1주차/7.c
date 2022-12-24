#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    int n, i;
    int* x, * y;

    scanf("%d", &n);

    x = (int*)malloc(sizeof(int) * n);
    if (x == NULL)
        return -1;

    y = (int*)malloc(sizeof(int) * n);
    if (y == NULL)
        return -1;

    for (i = 0; i < n; i++)
        scanf("%d", &x[i]);

    for (i = 0; i < n; i++)
        scanf("%d", &y[i]);

    for (i = 0; i < n; i++) {
        printf(" %d", x[i] + y[n - i - 1]);
    }

    free(y);
    free(x);

    return 0;
}