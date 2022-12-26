#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#pragma warning(disable:4996)

int* buildList(int n, int min, int max);
void writeList(int* L, int n);
int findKthSmallest(int* L, int n, int k);
void buildHeap(int* L, int n);
void downHeap(int* L, int index, int n);
void swapElements(int* L, int index1, int index2);
int removeMin(int* L, int n);
int* copy(int* L, int n);

int main() {

    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start, end, diff;
    int* L, * H;
    int output[5] = { 0 }, karray[4] = { 1, 100, 99900, 99999 };
    int i, k, result;

    srand(time(NULL));
    QueryPerformanceFrequency(&ticksPerSec);

    L = buildList(10, 1, 100);                  //�ʱ� ����Ʈ ����
    H = copy(L, 10);                            //�ʱ� ����Ʈ�� H�� ����
    writeList(L, 10);

    for (k = 1; k <= 3; k++) {
        L = copy(H, 10);                        //�ʱ� ����Ʈ�� L�� ����
        output[k] = findKthSmallest(L, 10, k);  //output�� ����� ����
    }

    writeList(output, 3);

    free(L);                            //�Ҵ���� ����Ʈ�� ����
    free(H);

    L = buildList(100000, 1, 1000000);  //�ʱ� ����Ʈ ����
    H = copy(L, 100000);                //�ʱ� ����Ʈ�� H�� ����

    for (k = 0; k < 4; k++) {

        L = copy(H, 100000);            //�ʱ� ����Ʈ�� L�� ����

        QueryPerformanceCounter(&start);

        result = findKthSmallest(L, 100000, karray[k]); //����� ����

        QueryPerformanceCounter(&end);

        diff.QuadPart = end.QuadPart - start.QuadPart;

        printf("%d %.8lf \n", result, ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));  //���, �ð� ���
    }

    free(L);
    free(H);

    return 0;
}

int* buildList(int n, int min, int max) {       //�ʱ� ����Ʈ ���� �Լ�

    int* L;
    int i;

    L = (int*)malloc(sizeof(int) * (n + 1));
    if (L == NULL)
        return -1;

    for (i = 1; i <= n; i++) {
        L[i] = ((1 << 16) * rand()) % max + min;
    }
    // L[i] = (((rand() << 15) | rand()) % max) + min;   //������ ����

    return L;
}

void writeList(int* L, int n) {     //��ü ��� ���

    int i;

    for (i = 1; i <= n; i++)
        printf("%d ", L[i]);

    printf("\n");

}

int findKthSmallest(int* L, int n, int k) {     //k��°�� ���� ���� �����ϴ� �Լ�

    int i, del = 0;

    buildHeap(L, n);            //O(n) �ð�

    for (i = 0; i < k; i++) {   //k�� �ݺ�
        del = removeMin(L, n);  //O(log(n)) �ð�
        n -= 1;
    }                           // ���� O(n + k log(n)) �ð��� ������

    return del;                 //k��° ���� ���� ��ȯ
}

void buildHeap(int* L, int n) {     //����� �� ����

    int i;

    for (i = n / 2; i >= 1; i--)
        downHeap(L, i, n);          //�� �Ӽ� ����
}

void downHeap(int* L, int index, int n) {

    int son;

    if (index * 2 > n)      //�ڽ� ��� ���� ��� ����
        return;

    son = index * 2;

    if (index * 2 + 1 <= n) {
        if (L[index * 2 + 1] < L[index * 2])
            son = index * 2 + 1;
    }

    if (L[index] <= L[son]) //�θ� �� ������ ����
        return;

    swapElements(L, index, son);

    downHeap(L, son, n);
}

void swapElements(int* L, int index1, int index2) { //��ȯ�ϴ� �Լ�

    int tmp;

    tmp = L[index1];
    L[index1] = L[index2];
    L[index2] = tmp;
}

int removeMin(int* L, int n) {  //��Ʈ�� ��ȯ�ϴ� �Լ�

    int key;

    key = L[1];
    L[1] = L[n];

    n -= 1;

    downHeap(L, 1, n);

    return key;
}

int* copy(int* L, int n) {  //����Ʈ�� ���� �����ϴ� �Լ�

    int* H;
    int i;

    H = (int*)malloc(sizeof(int) * (n + 1));
    if (H == NULL)
        return -1;

    for (i = 1; i <= n; i++)
        H[i] = L[i];

    return H;
}