#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int modulo(int a, int b) {
    while (a >= b) {
        a -= b;
    }
    return a;
}

int main(void)
{
    int a, b, result;

    scanf("%d %d", &a, &b);

    result = modulo(a, b);

    printf("%d", result);

    return 0;
}