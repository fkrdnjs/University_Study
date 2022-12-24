#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int sum(int n) {
    int i;
    int total = 0;

    for (i = 1; i <= n; i++)
        total += i;

    return total;
}

int main(void)
{
    int x;
    int i, result = 0;

    scanf("%d", &x);

    for (i = 1; i <= x; i++) {
        result += sum(i);
    }

    printf("%d", result);

    return 0;
}