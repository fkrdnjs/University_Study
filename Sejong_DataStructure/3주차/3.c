#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void num(int n) {

    if (n < 10)
        printf("%d\n", n);
    else {
        printf("%d\n", n % 10);
        num(n / 10);
    }

}

int main(void)
{
    int n;

    scanf("%d", &n);

    num(n);

    return 0;
}
