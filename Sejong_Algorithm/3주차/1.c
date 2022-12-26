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
        scanf("%c", &command);      //��ɾ� �Է�
        getchar();

        if (command == 'q')         //q�� ��� break
            break;
        else if (command == 'i') {  //i�� ��� ����
            scanf("%d", &key);
            getchar();

            insertItem(key);
            printf("0\n");
        }
        else if (command == 'd') {  //d�� ��� ����
            del = removeRoot();
            printf("%d\n", del);
        }
        else                        //p�� ��� ����Ʈ
            printHeap();
    }
    return 0;
}

void insertItem(int key) {  //���� �Լ�

    n += 1;                 //n 1 ���� �� key ����
    H[n] = key;

    upHeap(n);              //���� ����
}

int removeRoot() {

    int key;

    key = H[1];         //��Ʈ�� ����
    H[1] = H[n];        //��Ʈ �ڸ��� ���� key�� ����
    n -= 1;

    downHeap(1);        //����

    return key;         //��Ʈ�� ��ȯ
}

void upHeap(int index) {

    if (index == 1)                 //��Ʈ�� ��� ����
        return;
    if (H[index] <= H[index / 2])   //�θ𺸴� ������ ����
        return;

    swapElements(index, index / 2);

    upHeap(index / 2);
}

void downHeap(int index) {

    int son;

    if (index * 2 > n)          //�ڽ� ��� ���� ��� ����
        return;

    son = index * 2;

    if (H[index * 2 + 1] > H[index * 2])
        son = index * 2 + 1;

    if (H[index] >= H[son])     //�ڽ� ��庸�� Ŭ ��� ����
        return;

    swapElements(index, son);

    downHeap(son);
}

void printHeap() {          //��� �Լ�

    int i;

    for (i = 1; i <= n; i++)
        printf(" %d", H[i]);

    printf("\n");
}

void swapElements(int index1, int index2) { //��ȯ �Լ�

    int tmp;

    tmp = H[index1];
    H[index1] = H[index2];
    H[index2] = tmp;
}