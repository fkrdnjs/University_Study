#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct time {
    int hour;
    int minute;
    int cho;
}time;

int main(void)
{
    time x, y;
    int a, b, c;

    scanf("%d %d %d", &x.hour, &x.minute, &x.cho);
    scanf("%d %d %d", &y.hour, &y.minute, &y.cho);

    if (y.cho >= x.cho)
        c = y.cho - x.cho;
    else {
        y.minute -= 1;
        c = y.cho + 60 - x.cho;
    }

    if (y.minute >= x.minute)
        b = y.minute - x.minute;
    else {
        y.hour -= 1;
        b = y.minute + 60 - x.minute;
    }

    a = y.hour - x.hour;

    printf("%d %d %d", a, b, c);

    return 0;
}