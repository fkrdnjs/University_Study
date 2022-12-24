#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char x[201];
    int i, len;

    scanf("%s", x);
    len = strlen(x);

    for (i = 0; i < len; i++) {
        if (i != len - 1)
            printf("%s\n", x + i);
        else
            printf("%s", x + i);


        x[len + i] = x[i];
        x[len + i + 1] = '\0';
    }

    return 0;
}