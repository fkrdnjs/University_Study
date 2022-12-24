#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ABC(int x[], int k) {
    int max = x[k];
    int i, tmp, j;

    for (i = k; i < 10; i++) {
        if (x[i] >= max) {
            max = x[i];
            j = i;
        }
    }

    tmp = x[j];
    x[j] = x[k];
    x[k] = tmp;
}

int main(void)
{
    int x[10];
    int i, k;

    for (i = 0; i < 10; i++)
        scanf("%d", &x[i]);

    for (k = 0; k < 9; k++) {
        ABC(x, k);
    }

    for (i = 0; i < 10; i++)
        printf(" %d", x[i]);

    return 0;
}