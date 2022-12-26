#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable:4996)

int H[100];
int n = 0;

void upHeap(int index);
void insertItem(int key);
void downHeap(int index, int k);
void printArray();
void inPlaceHeapSort();
void swapElements(int index1, int index2);

int main() {

    int num;

    scanf("%d", &num);

    int key;

    for (int i = 0; i < num; i++) {
        scanf("%d", &key);
        insertItem(key);
    }

    inPlaceHeapSort();
    printArray();

    return 0;
}

void upHeap(int index) {

    if (index == 1)                 //��Ʈ�� ��� ����
        return;
    if (H[index] <= H[index / 2])   //�θ𺸴� ������ ����
        return;

    swapElements(index, index / 2);

    upHeap(index / 2);
}

void insertItem(int key) {  //���� �Լ�

    n += 1;                 //n 1 ���� �� key ����
    H[n] = key;

    upHeap(n);              //���� ����
}

void downHeap(int index, int k) {

    int son;

    if (index * 2 > k)      //�ڽ� ��� ���� ��� ����
        return;

    son = index * 2;

    if (index * 2 + 1 <= k) {
        if (H[index * 2 + 1] > H[index * 2])
            son = index * 2 + 1;
    }

    if (H[index] >= H[son])
        return;

    swapElements(index, son);

    downHeap(son, k);
}

void printArray() { //��� �Լ�

    for (int i = 1; i <= n; i++)
        printf(" %d", H[i]);
}

void inPlaceHeapSort() {

    int i;

    for (i = n; i >= 2; i--) {  //�ں��� �ִ� ä��, �� ������ ����
        swapElements(1, i);

        downHeap(1, i - 1);
    }
}

void swapElements(int index1, int index2) { //��ȯ �Լ�
    int tmp;

    tmp = H[index1];
    H[index1] = H[index2];
    H[index2] = tmp;
}