#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int maxnum(int x[20], int n, int i, int max) {

    if (i == n) {
        return max;
    }

    else {
        if (max < x[i])
            max = x[i];
    }

    maxnum(x, n, i + 1, max);

}

int main(void)
{
    int n, x[20];
    int i, res, max;

    scanf("%d", &n);

    for (i = 0; i < n; i++)
        scanf("%d", &x[i]);

    i = 0;
    max = x[i];

    res = maxnum(x, n, i + 1, max);

    printf("%d", res);

    return 0;
}
