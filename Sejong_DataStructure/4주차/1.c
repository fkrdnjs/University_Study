#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void change(int* x, int a, int b) {

    int tmp;

    while (a < b) {
        tmp = *(x + a);
        *(x + a) = *(x + b);
        *(x + b) = tmp;

        a += 1;
        b -= 1;
    }

}

int main(void) {

    int n, k, i;
    int x[100];
    int a, b;

    scanf("%d", &n);

    for (i = 0; i < n; i++)
        scanf("%d", &x[i]);

    scanf("%d", &k);

    for (i = 0; i < k; i++) {
        scanf("%d %d", &a, &b);
        change(x, a, b);
    }

    for (i = 0; i < n; i++)
        printf(" %d", x[i]);

    return 0;
}