#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {

    int n, * x;
    int i, j, tmp;
    int k;

    scanf("%d", &n);

    x = (int*)malloc(sizeof(int) * n);  //배열 동적할당
    if (x == NULL)
        return -1;

    for (i = 0; i < n; i++)             //배열 입력
        scanf("%d", &x[i]);

    for (i = 1; i < n; i++) {

        k = x[i];
        j = i - 1;

        while (1) {
            if (j == -1 || x[j] <= k)   //j가 0보다 작거나 x[j]보다 큰 수가 나오면 break
                break;

            x[j + 1] = x[j];            //한칸씩 미루는 과정
            j -= 1;
        }

        x[j + 1] = k;               //저장해놓은 수를 대입

    }

    for (i = 0; i < n; i++)         //전체 출력
        printf(" %d", x[i]);

    free(x);                    //프리

    return 0;
}