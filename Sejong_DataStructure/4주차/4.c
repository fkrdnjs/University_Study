#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int i = 0, j = 0, k = 1;

void left_right(int x[100][100]) {//왼 -> 오 채우는 함수

    for (j = j; x[i][j] == 0; j++) {
        x[i][j] = k++;
    }

    i += 1;
    j -= 1;
}

void right_left(int x[100][100]) {//오 -> 왼 채우는 함수

    for (j = j; x[i][j] == 0; j--) {
        x[i][j] = k++;
    }

    i -= 1;
    j += 1;
}

void up_down(int x[100][100]) {//위 -> 아래 채우는 함수

    for (i = i; x[i][j] == 0; i++) {
        x[i][j] = k++;
    }

    j -= 1;
    i -= 1;
}

void down_up(int x[100][100]) {//아래 -> 위 채우는 함수

    for (i = i; x[i][j] == 0; i--) {
        x[i][j] = k++;
    }

    j += 1;
    i += 1;
}

int main(void) {

    int n, m;
    int x[100][100] = { 0, };

    scanf("%d %d", &n, &m);

    if (n == 1) {//가로 한 줄일 경우

        for (j = 0; j < m; j++)
            x[i][j] = k++;

        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++)
                printf(" %d", x[i][j]);
            printf("\n");
        }

        return 0;

    }

    else if (m == 1) {//세로 한 줄일 경우

        for (i = 0; i < n; i++)
            x[i][j] = k++;

        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++)
                printf(" %d", x[i][j]);
            printf("\n");
        }

        return 0;
    }

    for (j = 0; j < m; j++)//위쪽 테두리 만들기
        x[i][j] = k++;

    j -= 1;

    for (i = 1; i < n; i++)//오른쪽 테두리 만들기
        x[i][j] = k++;

    i -= 1;

    for (j = j - 1; j >= 0; j--)//아래쪽 테두리 만들기
        x[i][j] = k++;

    j += 1;

    for (i = i - 1; i > 0; i--)//왼쪽 테두리 만들기
        x[i][j] = k++;

    i += 1;
    j += 1;

    while (k != n * m + 1) {

        left_right(x);
        up_down(x);
        right_left(x);
        down_up(x);

    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            printf(" %d", x[i][j]);
        printf("\n");
    }

    return 0;
}