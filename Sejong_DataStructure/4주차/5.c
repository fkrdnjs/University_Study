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

    x[0][0] = 1; //ù ������ 1�� ä����

    if (n == 1) {//���� �� ���� ���

        for (j = 1; j < m; j++)
            x[i][j] = k++;

        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++)
                printf(" %d", x[i][j]);
            printf("\n");
        }

        return 0;

    }

    else if (m == 1) {//���� �� ���� ���

        for (i = 1; i < n; i++)
            x[i][j] = k++;

        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++)
                printf(" %d", x[i][j]);
            printf("\n");
        }

        return 0;
    }

    //�� ���� ���
    while (k != n * m + 1) {

        f = 0;

        for (i = 0; i < n; i++) {//ä��� �����ؾ� �� �κ� ã�� ����
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
            x[i++][j--] = k++;//ä���

            if (j == -1 || i == n)//���� ù �ٿ� �����ϰų� ���� ������ �ٿ� �����ϸ� ����
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