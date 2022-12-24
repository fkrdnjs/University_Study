#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int gcd(int a, int b) {

    if (b == 0)
        return a;
    else {
        gcd(b, a % b);
    }
}

int main(void)
{
    int a, b, tmp;
    int res;

    scanf("%d %d", &a, &b);

    if (a < b) {// 무조건 a를 크게 만든다.
        tmp = a;
        a = b;
        b = tmp;
    }

    res = gcd(a, b);

    printf("%d", res);

    return 0;
}
