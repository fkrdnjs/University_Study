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

int findPivot(int left, int right) {    //랜덤으로 피벗 찾기

    int pivot;

    srand(time(NULL));

    pivot = rand() % (right - left + 1) + left;

    return pivot;
}

index inPlacePartition(int* x, int left, int right, int k) {

    index result;

    int i, j;
    int p = x[k];   //피벗 설정

    swapElements(&x[k], &x[right]); //피벗 가장 끝으로 이동

    i = left;
    j = right - 1;

    while (i <= j) {        //i, j 교차할때까지 분할

        while (i <= j && x[i] <= p)     //왼쪽부터 큰 원소 찾기
            i++;

        while (i <= j && x[j] >= p)     //오른쪽부터 작은 원소 찾기
            j--;

        if (i < j)
            swapElements(&x[i], &x[j]); //그룹 바꾸기
    }

    swapElements(&x[i], &x[right]); //피벗 원위치로

    result.a = i;
    j = right - 1;

    while ((i + 1) <= j && x[i + 1] == p)   //피벗과 같은 값 그룹 구간 구하기
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