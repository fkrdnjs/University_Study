#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int countOnesButSlow(int** A, int n) {

    int i, j, c;

    c = 0;
    for (i = 0; i < n; i++) {//ù°�ٺ��� �˻�
        j = 0;
        while (j < n && A[i][j] == 1) {//1�� ���� ��� �ݺ�
            c += 1;//1�� ��� �� ���� �ϸ鼭 ���������� �̵�
            j += 1;
        }
    }

    return c;

}

int countOnes(int** A, int n) {

    int cnt = 0;
    int i = 0, j = n - 1;

    while (i < n && j >= 0) {//ù°���� ���������� �˻� ����
        if (A[i][j] == 0) {//0�� ��� �������� ��ĭ �̵�
            j -= 1;
        }
        else {//1�� ��� cnt �� �ø��� �Ʒ��ٷ� �̵�
            cnt += j + 1;
            i += 1;
        }
    }

    return cnt;

}

int input(int** A, int n) {//�迭�� �Է��ϴ� �Լ�

    int kTotal = 0;//���� 1�� ���� ������ ����, ���ϰ�
    int cnt[3000];//1�� � �Է��ؾ����� ����ϴ� �迭, �� �ึ�� ��� 1�� �ִ��� ����ϴ� �迭
    int i, j;

    srand(time(NULL));

    //cnt�迭�� 0�� �ε����� n�� ���ؼ� �ʱ�ȭ�ϴ� �۾�
    cnt[0] = rand() % (int)(n - 0.9 * n + 1) + (int)(0.9 * n);

    //cnt�迭 1�� �ε������ʹ� i-1���� 1�� ������ ���ؼ� �־���
    for (i = 1; i < n; i++) {
        if (cnt[i - 1] * 0.9 > (int)(cnt[i - 1] * 0.9))//�� ������������ ���� ��
            cnt[i] = rand() % (int)(cnt[i - 1] - 0.9 * cnt[i - 1] + 1) + (int)(cnt[i - 1] * 0.9 + 1); //1 ũ�� ����
        else//�� ���� ��������
            cnt[i] = rand() % (int)(cnt[i - 1] - 0.9 * cnt[i - 1] + 1) + (int)(cnt[i - 1] * 0.9);//�׳� �ص� ��
    }

    //�迭 �ʱ�ȭ �۾��ϴ� �κ�
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (j < cnt[i]) {//���� ���� 1�� ������ 90�ۼ�Ʈ �̻�ŭ
                A[i][j] = 1;//�迭�� 1 ����
                kTotal += 1;//���� 1�� ���� ����
            }
            else {//�� ä������ ������ 0���� ����
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

    A = (int**)malloc(sizeof(int*) * 3000);//�迭 �����Ҵ�
    if (A == NULL)
        return -1;

    for (i = 0; i < 3000; i++) {//�����Ҵ�
        A[i] = (int*)malloc(sizeof(int) * 3000);
        if (A[i] == NULL)
            return -1;
    }

    //n=3000�϶�-----------------------------------------------------
    ktotal3 = input(A, 3000);

    QueryPerformanceCounter(&fst3);
    fast3 = countOnes(A, 3000);//���� �Լ� ����
    QueryPerformanceCounter(&fed3);

    QueryPerformanceCounter(&slst3);
    slow3 = countOnesButSlow(A, 3000);//���� �Լ� ����
    QueryPerformanceCounter(&sled3);

    fadf3.QuadPart = fed3.QuadPart - fst3.QuadPart;
    sldf3.QuadPart = sled3.QuadPart - slst3.QuadPart;

    //n=1000�϶�-------------------------------------------------------
    ktotal1 = input(A, 1000);

    QueryPerformanceCounter(&fst1);
    fast1 = countOnes(A, 1000);//���� �Լ� ����
    QueryPerformanceCounter(&fed1);

    QueryPerformanceCounter(&slst1);
    slow1 = countOnesButSlow(A, 1000);//���� �Լ� ����
    QueryPerformanceCounter(&sled1);

    fadf1.QuadPart = fed1.QuadPart - fst1.QuadPart;
    sldf1.QuadPart = sled1.QuadPart - slst1.QuadPart;

    //n=2000�϶�--------------------------------------------------------
    ktotal2 = input(A, 2000);

    QueryPerformanceCounter(&fst2);
    fast2 = countOnes(A, 2000);//���� �Լ� ����
    QueryPerformanceCounter(&fed2);

    QueryPerformanceCounter(&slst2);
    slow2 = countOnesButSlow(A, 2000);//���� �Լ� ����
    QueryPerformanceCounter(&sled2);

    fadf2.QuadPart = fed2.QuadPart - fst2.QuadPart;
    sldf2.QuadPart = sled2.QuadPart - slst2.QuadPart;

    //���� 1�� ��, �Լ� ���� ���, ����ð� ���
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