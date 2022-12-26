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

    if (index == 1)                 //루트일 경우 리턴
        return;
    if (H[index] <= H[index / 2])   //부모보다 작으면 리턴
        return;

    swapElements(index, index / 2);

    upHeap(index / 2);
}

void insertItem(int key) {  //삽입 함수

    n += 1;                 //n 1 증가 후 key 대입
    H[n] = key;

    upHeap(n);              //순서 정렬
}

void downHeap(int index, int k) {

    int son;

    if (index * 2 > k)      //자식 노드 없을 경우 리턴
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

void printArray() { //출력 함수

    for (int i = 1; i <= n; i++)
        printf(" %d", H[i]);
}

void inPlaceHeapSort() {

    int i;

    for (i = n; i >= 2; i--) {  //뒤부터 최댓값 채움, 힙 사이즈 감소
        swapElements(1, i);

        downHeap(1, i - 1);
    }
}

void swapElements(int index1, int index2) { //교환 함수
    int tmp;

    tmp = H[index1];
    H[index1] = H[index2];
    H[index2] = tmp;
}