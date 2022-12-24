#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct student {
    char name[10];
    int grade;
}st;

int main(void)
{
    st x[5];
    int i, total = 0, cnt = 0;
    double avg;

    for (i = 0; i < 5; i++) {
        scanf("%s %d", x[i].name, &x[i].grade);
        total += x[i].grade;
    }

    avg = (double)total / 5.0;

    for (i = 0; i < 5; i++) {
        if (x[i].grade < avg)
            cnt += 1;
    }

    for (i = 0; i < 5; i++) {
        if (x[i].grade < avg) {
            cnt -= 1;
            if (cnt != 1)
                printf("%s\n", x[i].name);
            else
                printf("%s", x[i].name);
        }
    }

    return 0;
}