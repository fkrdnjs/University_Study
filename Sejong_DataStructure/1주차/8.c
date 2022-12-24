#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct student {
    char name[8];
    int kor;
    int eng;
    int math;
    double avg;
}st;

int main(void)
{
    int n, i;
    int total = 0;
    st* x;

    scanf("%d", &n);

    x = (st*)malloc(sizeof(st) * n);
    if (x == NULL)
        return -1;

    for (i = 0; i < n; i++) {
        total = 0;

        scanf("%s %d %d %d", x[i].name, &x[i].kor, &x[i].eng, &x[i].math);
        total = x[i].kor + x[i].eng + x[i].math;

        x[i].avg = (double)total / 3.0;
    }

    for (i = 0; i < n; i++) {
        printf("%s %.1lf", x[i].name, x[i].avg);

        if (x[i].kor >= 90 || x[i].eng >= 90 || x[i].math >= 90)
            printf(" GREAT");

        if (x[i].kor < 70 || x[i].eng < 70 || x[i].math < 70)
            printf(" BAD");

        if (i != n - 1)
            printf("\n");
    }

    free(x);

    return 0;
}