#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {

    int n, * x;
    int i, j, tmp, max;
    int index = 0;

    scanf("%d", &n);

    x = (int*)malloc(sizeof(int) * n);  //동적할당 과정
    if (x == NULL)
        return -1;

    for (i = 0; i < n; i++)             //배열 입력
        scanf("%d", &x[i]);

    for (i = 0; i < n - 1; i++) {
        max = -1;

        for (j = 0; j < n - i; j++) {   //가장 큰 수 찾는 과정
            if (max < x[j]) {
                max = x[j];             //max에 가장 큰 수   저장
                index = j;              //index는 가장 큰 수의 인덱스 저장
            }
        }

        tmp = x[index];                 //가장 큰 수와 n-i-1 수와 교환
        x[index] = x[n - 1 - i];
        x[n - 1 - i] = tmp;

    }

    for (i = 0; i < n; i++)             //전체 프린트
        printf(" %d", x[i]);

    free(x);

    return 0;
}