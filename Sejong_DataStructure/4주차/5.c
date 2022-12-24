#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

    int n, m;
    int x[100][100] = { 0, };
    int i = 0, j = 0, k = 2, f = 0;

    scanf("%d %d", &n, &m);

    x[0][0] = 1; //첫 공간은 1로 채워줌

    if (n == 1) {//가로 한 줄일 경우

        for (j = 1; j < m; j++)
            x[i][j] = k++;

        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++)
                printf(" %d", x[i][j]);
            printf("\n");
        }

        return 0;

    }

    else if (m == 1) {//세로 한 줄일 경우

        for (i = 1; i < n; i++)
            x[i][j] = k++;

        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++)
                printf(" %d", x[i][j]);
            printf("\n");
        }

        return 0;
    }

    //그 외의 경우
    while (k != n * m + 1) {

        f = 0;

        for (i = 0; i < n; i++) {//채우기 시작해야 될 부분 찾는 과정
            for (j = 0; j < m; j++) {
                if (x[i][j] == 0) {
                    f = 1;
                    break;
                }
            }
            if (f == 1)
                break;
        }

        while (1) {
            x[i++][j--] = k++;//채우기

            if (j == -1 || i == n)//세로 첫 줄에 도달하거나 가로 마지막 줄에 도달하면 종료
                break;
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf(" %d", x[i][j]);
        }
        printf("\n");
    }

    return 0;
}