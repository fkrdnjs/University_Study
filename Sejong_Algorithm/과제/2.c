#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include <Windows.h>
#pragma warning(disable:4996)

int n = 100000;
int Limits[4] = { 1, 100, 500, 1000 };
int Limit;

int* copy(int* A);
void swapElements(int* x, int* y);
int findIndexOfMedianOfThree(int* A, int a, int b, int c);
int findPivot(int* A, int l, int r, int mode);
int inPlacePartition(int* A, int l, int r, int k);
int* createArray();
void rQuickSort(int* A, int l, int r, int mode);
void insertionSort(int* A);
void quickSort(int* A, int mode);

int main() {

    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start, end, diff;
    int* A, * AC;
    int i, j;

    QueryPerformanceFrequency(&ticksPerSec);

    srand(time(NULL));

    A = createArray();

    printf("Limit  결정적1       결정적3       무작위1       무작위3\n");

    for (i = 0; i < 4; i++) {
        printf("%4d ", Limits[i]);
        Limit = Limits[i];

        for (j = 0; j < 4; j++) {
            AC = copy(A);

            QueryPerformanceCounter(&start);
            quickSort(AC, j);
            QueryPerformanceCounter(&end);

            diff.QuadPart = end.QuadPart - start.QuadPart;

            printf(" %12.8f/ms", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

        }
        free(AC);
        printf("\n");
    }

    free(A);

    return 0;
}

int* copy(int* A) {     //배열 복사하는 함수

    int* AC;
    int i;

    AC = (int*)malloc(sizeof(int) * n); //배열 동적할당
    if (AC == NULL)
        return -1;

    for (i = 0; i < n; i++)         //배열 복사후 반환
        AC[i] = A[i];

    return AC;
}

void swapElements(int* x, int* y) { //swap 함수

    int tmp;

    tmp = *x;
    *x = *y;
    *y = tmp;
}

int findIndexOfMedianOfThree(int* A, int a, int b, int c) { //피벗 중 중간 값 반환

    if ((A[b] >= A[a] && A[a] >= A[c]) || (A[c] >= A[a] && A[a] >= A[b]))
        return a;
    else if ((A[a] >= A[b] && A[b] >= A[c]) || (A[c] >= A[b] && A[b] >= A[a]))
        return b;
    else if ((A[a] >= A[c] && A[c] >= A[b]) || (A[b] >= A[c] && A[c] >= A[a]))
        return c;
}


int findPivot(int* A, int l, int r, int mode) { //피벗 찾는 함수
    int a, b, c;

    if (mode == 0)      //결정적 1일 경우
        return r;

    else if (mode == 2)     //무작위 1일 경우
        return ((1 << 16) * rand()) % (r - l) + l;

    if (r - l == 1)
        return l;

    if (mode == 1)      //결정적 3일 경우
        return findIndexOfMedianOfThree(A, l, (l + r) / 2, r);

    if (mode == 3) {    //무작위 3일 경우
        a = ((1 << 16) * rand()) % (r - l) + l;
        b = ((1 << 16) * rand()) % (r - l) + l;
        c = ((1 << 16) * rand()) % (r - l) + l;

        return findIndexOfMedianOfThree(A, a, b, c);
    }
}

int inPlacePartition(int* A, int l, int r, int k) {

    int i = l, j = r - 1;
    int p = A[k];

    swapElements(&A[k], &A[r]);     //피벗과 가장 오른쪽 교환

    while (i <= j) {
        while (i <= j && A[i] < p)  //중복키 배제를 위해 = 연산 제거
            i = i + 1;

        while (j >= i && A[j] >= p)
            j = j - 1;

        if (i < j)
            swapElements(&A[i], &A[j]);
    }

    swapElements(&A[i], &A[r]);

    j = r - 1;

    while (i <= j) {
        while (i <= j && A[i] == p)
            j = j - 1;

        if (i < j && A[i] == p)
            swapElements(&A[i], &A[j]);
    }

    return i;
}

int* createArray() {        //배열 생성하는 함수
    int* A;

    A = (int*)malloc(sizeof(int) * n);  //배열 동적할당
    if (A == NULL)
        return -1;

    for (int i = 0; i < n; i++)
        A[i] = ((1 << 16) * rand()) % n + 1;    //랜덤값 배열에 저장

    return A;
}

void rQuickSort(int* A, int l, int r, int mode) {
    int pivot, k2, k3, k4;

    if (r - l >= Limit) {
        pivot = findPivot(A, l, r, mode);

        k3 = k4 = inPlacePartition(A, l, r, pivot);

        while (1) {
            if (A[k4] != A[k3]) {
                k2 = k4 + 1;
                break;
            }
            k4--;
        }

        rQuickSort(A, l, k2 - 1, mode);
        rQuickSort(A, k3 + 1, r, mode);
    }
}

void insertionSort(int* A) {        //삽입 정렬

    int i, j;
    int k;

    for (i = 1; i < n; i++) {
        k = A[i];
        j = i - 1;

        while (1) {
            if (j == -1 || A[j] <= k)
                break;

            A[j + 1] = A[j];
            j -= 1;
        }

        A[j + 1] = k;
    }
}

void quickSort(int* A, int mode) {

    rQuickSort(A, 0, n - 1, mode);

    if (Limit > 1)                  //rquicksort 안들어가면 삽입정렬로
        insertionSort(A);

    return;
}