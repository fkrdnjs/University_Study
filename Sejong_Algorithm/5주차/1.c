#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable:4996)

typedef struct node {
    int data;
    struct node* next;
}node;

node* getnode();
node* mergeSort(node* L, int n);
node* partition(node* L, int k);
node* merge(node* L1, node* L2);
node* newItem(node* k, int elem);
void freehelp(node* header);

int main() {

    int n, i, elem;
    node* header, * p;

    scanf("%d", &n);

    header = getnode();
    p = header;

    for (i = 0; i < n; i++) {
        scanf("%d", &elem);
        p = newItem(p, elem);
    }

    p = header->next;
    p = mergeSort(p, n);

    while (p != NULL) {
        printf(" %d", p->data);
        p = p->next;
    }

    freehelp(header);

    return 0;
}

void freehelp(node* header) {   //할당 노드 프리하는 함수

    node* p, * del;

    p = header;

    while (p != NULL) {
        del = p;
        p = p->next;

        free(del);
    }
}

node* getnode() {       //노드 동적할당 함수, 데이터는 넣지 않고 할당만 받음

    node* new = (node*)malloc(sizeof(node));
    if (new == NULL)
        return -1;

    new->next = NULL;

    return new;
}

node* mergeSort(node* L, int n) {

    if (n == 1)                     //리스트의 갯수가 1이면 그냥 바로 리스트를 반환
        return L;

    node* l1, * l2;
    int k = n / 2;                  //절반으로 나누기

    l1 = L;                         //L1은 인자로 받은 리스트를 가리키도록
    l2 = partition(L, k);           //partition 함수로 나눈 나머지를 L2가 가리키도록 함

    l1 = mergeSort(l1, k);          //재귀로 반복
    l2 = mergeSort(l2, n - k);

    return merge(l1, l2);           //나눠진 두 개의 리스트를 merge로 합치기
}

node* partition(node* L, int k) {   //전체 리스트 L을 k의 크기로 나누는 함수

    node* L2 = NULL;
    int i;

    for (i = 0; i < k - 1; i++)     //k만큼 L 이동
        L = L->next;

    L2 = L->next;                   //L2에 L의 next 연결
    L->next = NULL;                 //next를 NULL로 초기화해서 연결 끊기

    return L2;                      //L2를 반환
}

node* merge(node* L1, node* L2) {       //두 개의 리스트 합치는 함수

    node* p;

    if (L1->data > L2->data) {          //L1 과 L2 중 더 작은 곳에 p를 연결한다.
        p = L2;
        L2 = L2->next;
    }
    else {
        p = L1;
        L1 = L1->next;
    }

    node* k = p;                    //p의 시작 주소를 저장하는 k

    while (L1 != NULL && L2 != NULL) {  //둘 중 하나가 끝이 날 때까지 반복

        if (L1->data > L2->data) {
            p->next = L2;
            L2 = L2->next;
        }
        else {
            p->next = L1;
            L1 = L1->next;
        }
        p = p->next;
    }

    while (L1 != NULL) {            //L1이 남아있으면 L1 끝까지 p에 연결
        p->next = L1;
        L1 = L1->next;
        p = p->next;
    }

    while (L2 != NULL) {            //L2가 남아있으면 L2 끝까지 p에 연결
        p->next = L2;
        L2 = L2->next;
        p = p->next;
    }

    return k;                   //p에 다 연결되었으니 p의 시작지점인 k를 반환
}

node* newItem(node* k, int elem) {  //노드에 데이터 넣고 next 연결하는 함수

    node* a = getnode();

    a->data = elem;
    k->next = a;

    return a;
}