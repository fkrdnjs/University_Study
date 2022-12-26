#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {

    int n, * x;
    int i, j, tmp;
    int k;

    scanf("%d", &n);

    x = (int*)malloc(sizeof(int) * n);  //�迭 �����Ҵ�
    if (x == NULL)
        return -1;

    for (i = 0; i < n; i++)             //�迭 �Է�
        scanf("%d", &x[i]);

    for (i = 1; i < n; i++) {

        k = x[i];
        j = i - 1;

        while (1) {
            if (j == -1 || x[j] <= k)   //j�� 0���� �۰ų� x[j]���� ū ���� ������ break
                break;

            x[j + 1] = x[j];            //��ĭ�� �̷�� ����
            j -= 1;
        }

        x[j + 1] = k;               //�����س��� ���� ����

    }

    for (i = 0; i < n; i++)         //��ü ���
        printf(" %d", x[i]);

    free(x);                    //����

    return 0;
}