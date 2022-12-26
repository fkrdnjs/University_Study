#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable:4996)

int H[100];
int n = 0;

void insertItem(int key);
int removeRoot();
void upHeap(int index);
void downHeap(int index);
void printHeap();
void swapElements(int index1, int index2);

int main() {

    char command;
    int key, del;

    while (1) {
        scanf("%c", &command);      //명령어 입력
        getchar();

        if (command == 'q')         //q일 경우 break
            break;
        else if (command == 'i') {  //i일 경우 삽입
            scanf("%d", &key);
            getchar();

            insertItem(key);
            printf("0\n");
        }
        else if (command == 'd') {  //d일 경우 삭제
            del = removeRoot();
            printf("%d\n", del);
        }
        else                        //p일 경우 프린트
            printHeap();
    }
    return 0;
}

void insertItem(int key) {  //삽입 함수

    n += 1;                 //n 1 증가 후 key 대입
    H[n] = key;

    upHeap(n);              //순서 정렬
}

int removeRoot() {

    int key;

    key = H[1];         //루트값 저장
    H[1] = H[n];        //루트 자리에 현재 key값 대입
    n -= 1;

    downHeap(1);        //정렬

    return key;         //루트값 반환
}

void upHeap(int index) {

    if (index == 1)                 //루트일 경우 리턴
        return;
    if (H[index] <= H[index / 2])   //부모보다 작으면 리턴
        return;

    swapElements(index, index / 2);

    upHeap(index / 2);
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