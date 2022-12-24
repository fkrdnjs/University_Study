#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int countOnesButSlow(int A[100][100], int n) {

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

int countOnes(int A[100][100], int n) {

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

int main(void)
{
    int n, A[100][100];
    int i, j;
    int slow, fast;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);//�Է� ����
        }
    }

    slow = countOnesButSlow(A, n);//���� �Լ� ��� 
    fast = countOnes(A, n);//���� �Լ� ���

    printf("%d\n%d", slow, fast);

    return 0;
}
