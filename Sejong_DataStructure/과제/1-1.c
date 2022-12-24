#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int countOnesButSlow(int A[100][100], int n) {

    int i, j, c;

    c = 0;
    for (i = 0; i < n; i++) {//첫째줄부터 검사
        j = 0;
        while (j < n && A[i][j] == 1) {//1인 동안 계속 반복
            c += 1;//1일 경우 값 증가 하면서 오른쪽으로 이동
            j += 1;
        }
    }

    return c;

}

int countOnes(int A[100][100], int n) {

    int cnt = 0;
    int i = 0, j = n - 1;

    while (i < n && j >= 0) {//첫째줄의 마지막부터 검사 시작
        if (A[i][j] == 0) {//0일 경우 왼쪽으로 한칸 이동
            j -= 1;
        }
        else {//1일 경우 cnt 값 늘리고 아래줄로 이동
            cnt += j + 1;
            i += 1;
        }
    }

    return cnt;

}

int main(void)
{
    int n, A[100][100];
    int i, j;
    int slow, fast;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);//입력 받음
        }
    }

    slow = countOnesButSlow(A, n);//느린 함수 결과 
    fast = countOnes(A, n);//빠른 함수 결과

    printf("%d\n%d", slow, fast);

    return 0;
}
