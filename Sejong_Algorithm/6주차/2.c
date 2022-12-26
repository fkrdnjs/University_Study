#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable:4996)

int find(int* x, int k, int left, int right);

int main() {

    int n, k, i, result;
    int* x;

    scanf("%d %d", &n, &k);

    x = (int*)malloc(sizeof(int) * n);		//�迭 �����Ҵ�
    if (x == NULL)
        return -1;

    for (i = 0; i < n; i++)
        scanf("%d", &x[i]);

    if (k > x[n - 1])                       //x �� k�� �����ϴ� ���� ���� ��� n ���
        printf(" %d", n);
    else {                                  //x �� k�� �����ϴ� ���� ���� ���
        result = find(x, k, 0, n - 1);

        printf(" %d", result);
    }
    free(x);								//�迭 ����

    return 0;
}

int find(int* x, int k, int left, int right) {

    int mid;

    while (1) {

        mid = (left + right) / 2;       //��� �ε���

        if (x[mid] == k)                //��� ���� key�� ��ġ�� ��� mid ��ȯ
            return mid;
        if (left > right)               //left, right�� ������ ��� left ��ȯ
            return left;

        if (k < x[mid])                 //��� ������ key�� ���� ��� right�� mid-1�� �ϰ� �ݺ�
            right = mid - 1;
        else                            //��� ������ key�� Ŭ ��� elft�� mid+1�� �ϰ� �ݺ�
            left = mid + 1;
    }

}