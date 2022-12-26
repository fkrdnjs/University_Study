#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#pragma warning(disable:4996)

typedef struct index {
    int a;
    int b;
}index;

int findPivot(int left, int right);
index inPlacePartition(int* x, int left, int right, int k);
void inPlaceQuickSort(int* x, int left, int right);
void swapElements(int* a, int* b);
void printhelp(int* x, int n);

int main() {

    int n, i;
    int* x;

    scanf("%d", &n);

    x = (int*)malloc(sizeof(int) * n);
    if (x == NULL)
        return -1;

    for (i = 0; i < n; i++)
        scanf("%d", &x[i]);

    inPlaceQuickSort(x, 0, n - 1);

    printhelp(x, n);

    free(x);
}

int findPivot(int left, int right) {    //�������� �ǹ� ã��

    int pivot;

    srand(time(NULL));

    pivot = rand() % (right - left + 1) + left;

    return pivot;
}

index inPlacePartition(int* x, int left, int right, int k) {

    index result;

    int i, j;
    int p = x[k];   //�ǹ� ����

    swapElements(&x[k], &x[right]); //�ǹ� ���� ������ �̵�

    i = left;
    j = right - 1;

    while (i <= j) {        //i, j �����Ҷ����� ����

        while (i <= j && x[i] <= p)     //���ʺ��� ū ���� ã��
            i++;

        while (i <= j && x[j] >= p)     //�����ʺ��� ���� ���� ã��
            j--;

        if (i < j)
            swapElements(&x[i], &x[j]); //�׷� �ٲٱ�
    }

    swapElements(&x[i], &x[right]); //�ǹ� ����ġ��

    result.a = i;
    j = right - 1;

    while ((i + 1) <= j && x[i + 1] == p)   //�ǹ��� ���� �� �׷� ���� ���ϱ�
        i++;

    result.b = i;

    return result;
}

void inPlaceQuickSort(int* x, int left, int right) {

    if (left >= right)
        return;

    index result;

    int pivot;

    pivot = findPivot(left, right);

    result = inPlacePartition(x, left, right, pivot);

    inPlaceQuickSort(x, left, result.a - 1);
    inPlaceQuickSort(x, result.b + 1, right);
}

void swapElements(int* a, int* b) {

    int tmp;

    tmp = *b;
    *b = *a;
    *a = tmp;
}

void printhelp(int* x, int n) {

    int i;

    for (i = 0; i < n; i++)
        printf(" %d", x[i]);

}