#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap(int* a, int* b) {

    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;

}

int main(void)
{
    int n, a, b, i;
    int x[50];

    scanf("%d", &n);

    for (i = 0; i < n; i++)
        scanf("%d", &x[i]);

    scanf("%d %d", &a, &b);

    swap(x + a, x + b);

    for (i = 0; i < n; i++)
        printf(" %d", x[i]);

    return 0;
}