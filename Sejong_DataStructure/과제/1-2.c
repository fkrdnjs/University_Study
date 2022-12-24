#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int countOnesButSlow(int** A, int n) {

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

int countOnes(int** A, int n) {

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

int input(int** A, int n) {//배열에 입력하는 함수

    int kTotal = 0;//실제 1의 갯수 저장할 변수, 리턴값
    int cnt[3000];//1을 몇개 입력해야할지 계산하는 배열, 각 행마다 몇개의 1이 있는지 계산하는 배열
    int i, j;

    srand(time(NULL));

    //cnt배열의 0번 인덱스를 n과 비교해서 초기화하는 작업
    cnt[0] = rand() % (int)(n - 0.9 * n + 1) + (int)(0.9 * n);

    //cnt배열 1번 인덱스부터는 i-1행의 1의 갯수와 비교해서 넣어줌
    for (i = 1; i < n; i++) {
        if (cnt[i - 1] * 0.9 > (int)(cnt[i - 1] * 0.9))//딱 나눠떨어지지 않을 때
            cnt[i] = rand() % (int)(cnt[i - 1] - 0.9 * cnt[i - 1] + 1) + (int)(cnt[i - 1] * 0.9 + 1); //1 크게 해줌
        else//딱 나눠 떨어지면
            cnt[i] = rand() % (int)(cnt[i - 1] - 0.9 * cnt[i - 1] + 1) + (int)(cnt[i - 1] * 0.9);//그냥 해도 됨
    }

    //배열 초기화 작업하는 부분
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (j < cnt[i]) {//이전 행의 1의 갯수의 90퍼센트 이상만큼
                A[i][j] = 1;//배열에 1 저장
                kTotal += 1;//실제 1의 갯수 저장
            }
            else {//다 채웠으면 나머지 0으로 저장
                A[i][j] = 0;
            }
        }
    }

    return kTotal;

}

int main(void) {

    int** A, i;
    int slow1, slow2, slow3, fast1, fast2, fast3;
    int ktotal1 = 0, ktotal2 = 0, ktotal3 = 0;
    LARGE_INTEGER ticks;
    LARGE_INTEGER slst1, slst2, slst3, sled1, sled2, sled3;
    LARGE_INTEGER fst1, fst2, fst3, fed1, fed2, fed3;
    LARGE_INTEGER sldf1, sldf2, sldf3, fadf1, fadf2, fadf3;

    QueryPerformanceFrequency(&ticks);

    A = (int**)malloc(sizeof(int*) * 3000);//배열 동적할당
    if (A == NULL)
        return -1;

    for (i = 0; i < 3000; i++) {//동적할당
        A[i] = (int*)malloc(sizeof(int) * 3000);
        if (A[i] == NULL)
            return -1;
    }

    //n=3000일때-----------------------------------------------------
    ktotal3 = input(A, 3000);

    QueryPerformanceCounter(&fst3);
    fast3 = countOnes(A, 3000);//빠른 함수 실행
    QueryPerformanceCounter(&fed3);

    QueryPerformanceCounter(&slst3);
    slow3 = countOnesButSlow(A, 3000);//느린 함수 실행
    QueryPerformanceCounter(&sled3);

    fadf3.QuadPart = fed3.QuadPart - fst3.QuadPart;
    sldf3.QuadPart = sled3.QuadPart - slst3.QuadPart;

    //n=1000일때-------------------------------------------------------
    ktotal1 = input(A, 1000);

    QueryPerformanceCounter(&fst1);
    fast1 = countOnes(A, 1000);//빠른 함수 실행
    QueryPerformanceCounter(&fed1);

    QueryPerformanceCounter(&slst1);
    slow1 = countOnesButSlow(A, 1000);//느린 함수 실행
    QueryPerformanceCounter(&sled1);

    fadf1.QuadPart = fed1.QuadPart - fst1.QuadPart;
    sldf1.QuadPart = sled1.QuadPart - slst1.QuadPart;

    //n=2000일때--------------------------------------------------------
    ktotal2 = input(A, 2000);

    QueryPerformanceCounter(&fst2);
    fast2 = countOnes(A, 2000);//빠른 함수 실행
    QueryPerformanceCounter(&fed2);

    QueryPerformanceCounter(&slst2);
    slow2 = countOnesButSlow(A, 2000);//느린 함수 실행
    QueryPerformanceCounter(&sled2);

    fadf2.QuadPart = fed2.QuadPart - fst2.QuadPart;
    sldf2.QuadPart = sled2.QuadPart - slst2.QuadPart;

    //실제 1의 수, 함수 실행 결과, 실행시간 출력
    printf("%d, %d, %.9lf\n", ktotal3, fast3, (double)fadf3.QuadPart / (double)ticks.QuadPart);
    printf("%d, %d, %.9lf\n", ktotal1, fast1, (double)fadf1.QuadPart / (double)ticks.QuadPart);
    printf("%d, %d, %.9lf\n", ktotal2, fast2, (double)fadf2.QuadPart / (double)ticks.QuadPart);

    printf("%d, %d, %.9lf\n", ktotal3, slow3, (double)sldf3.QuadPart / (double)ticks.QuadPart);
    printf("%d, %d, %.9lf\n", ktotal1, slow1, (double)sldf1.QuadPart / (double)ticks.QuadPart);
    printf("%d, %d, %.9lf\n", ktotal2, slow2, (double)sldf2.QuadPart / (double)ticks.QuadPart);

    for (i = 0; i < 3000; i++)
        free(A[i]);
    free(A);

    return 0;
}