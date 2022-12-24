#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int sum(int n) {

    if (n == 1)
        return 1;
    else
        return n + sum(n - 1);
}

int main(void)
{
    int n;
    int result;

    scanf("%d", &n);

    result = sum(n);

    printf("%d", result);

    return 0;
}
