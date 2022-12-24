#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int index(char* x, char k, int cnt) {

    if (*x == '\0')
        return cnt;
    else {
        if (*x == k)
            cnt += 1;
        index(x + 1, k, cnt);
    }

}

int main(void)
{
    char x[101], k;
    int res, cnt = 0;

    scanf("%s", x);
    getchar();

    scanf("%c", &k);

    res = index(x, k, cnt);

    printf("%d", res);

    return 0;
}
