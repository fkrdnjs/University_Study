#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {

    int n, * x;
    int i, j, tmp, max;
    int index = 0;

    scanf("%d", &n);

    x = (int*)malloc(sizeof(int) * n);  //�����Ҵ� ����
    if (x == NULL)
        return -1;

    for (i = 0; i < n; i++)             //�迭 �Է�
        scanf("%d", &x[i]);

    for (i = 0; i < n - 1; i++) {
        max = -1;

        for (j = 0; j < n - i; j++) {   //���� ū �� ã�� ����
            if (max < x[j]) {
                max = x[j];             //max�� ���� ū ��   ����
                index = j;              //index�� ���� ū ���� �ε��� ����
            }
        }

        tmp = x[index];                 //���� ū ���� n-i-1 ���� ��ȯ
        x[index] = x[n - 1 - i];
        x[n - 1 - i] = tmp;

    }

    for (i = 0; i < n; i++)             //��ü ����Ʈ
        printf(" %d", x[i]);

    free(x);

    return 0;
}