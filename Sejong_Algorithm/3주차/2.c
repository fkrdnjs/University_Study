#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable:4996)

int H[100];
int n = 0;

void buildHeap();
void downHeap(int index);
void printHeap();
void swapElements(int index1, int index2);

int main() {

    int i;

    scanf("%d", &n);

    for (i = 1; i <= n; i++)
        scanf("%d", &H[i]);

    buildHeap();

    printHeap();

    return 0;
}

void buildHeap() {

    int i;

    for (i = n / 2; i >= 1; i--)    //마지막 노드부터 루트까지 정렬
        downHeap(i);
}

void downHeap(int index) {

    int son;

    if (index * 2 > n)          //자식 노드 없을 경우 리턴
        return;

    son = index * 2;

    if (H[index * 2 + 1] > H[index * 2])
        son = index * 2 + 1;

    if (H[index] >= H[son])     //자식 노드보다 클 경우 리턴
        return;

    swapElements(index, son);

    downHeap(son);
}

void printHeap() {          //출력 함수

    int i;

    for (i = 1; i <= n; i++)
        printf(" %d", H[i]);

    printf("\n");
}

void swapElements(int index1, int index2) { //교환 함수

    int tmp;

    tmp = H[index1];
    H[index1] = H[index2];
    H[index2] = tmp;
}