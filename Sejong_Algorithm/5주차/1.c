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

void freehelp(node* header) {   //�Ҵ� ��� �����ϴ� �Լ�

    node* p, * del;

    p = header;

    while (p != NULL) {
        del = p;
        p = p->next;

        free(del);
    }
}

node* getnode() {       //��� �����Ҵ� �Լ�, �����ʹ� ���� �ʰ� �Ҵ縸 ����

    node* new = (node*)malloc(sizeof(node));
    if (new == NULL)
        return -1;

    new->next = NULL;

    return new;
}

node* mergeSort(node* L, int n) {

    if (n == 1)                     //����Ʈ�� ������ 1�̸� �׳� �ٷ� ����Ʈ�� ��ȯ
        return L;

    node* l1, * l2;
    int k = n / 2;                  //�������� ������

    l1 = L;                         //L1�� ���ڷ� ���� ����Ʈ�� ����Ű����
    l2 = partition(L, k);           //partition �Լ��� ���� �������� L2�� ����Ű���� ��

    l1 = mergeSort(l1, k);          //��ͷ� �ݺ�
    l2 = mergeSort(l2, n - k);

    return merge(l1, l2);           //������ �� ���� ����Ʈ�� merge�� ��ġ��
}

node* partition(node* L, int k) {   //��ü ����Ʈ L�� k�� ũ��� ������ �Լ�

    node* L2 = NULL;
    int i;

    for (i = 0; i < k - 1; i++)     //k��ŭ L �̵�
        L = L->next;

    L2 = L->next;                   //L2�� L�� next ����
    L->next = NULL;                 //next�� NULL�� �ʱ�ȭ�ؼ� ���� ����

    return L2;                      //L2�� ��ȯ
}

node* merge(node* L1, node* L2) {       //�� ���� ����Ʈ ��ġ�� �Լ�

    node* p;

    if (L1->data > L2->data) {          //L1 �� L2 �� �� ���� ���� p�� �����Ѵ�.
        p = L2;
        L2 = L2->next;
    }
    else {
        p = L1;
        L1 = L1->next;
    }

    node* k = p;                    //p�� ���� �ּҸ� �����ϴ� k

    while (L1 != NULL && L2 != NULL) {  //�� �� �ϳ��� ���� �� ������ �ݺ�

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

    while (L1 != NULL) {            //L1�� ���������� L1 ������ p�� ����
        p->next = L1;
        L1 = L1->next;
        p = p->next;
    }

    while (L2 != NULL) {            //L2�� ���������� L2 ������ p�� ����
        p->next = L2;
        L2 = L2->next;
        p = p->next;
    }

    return k;                   //p�� �� ����Ǿ����� p�� ���������� k�� ��ȯ
}

node* newItem(node* k, int elem) {  //��忡 ������ �ְ� next �����ϴ� �Լ�

    node* a = getnode();

    a->data = elem;
    k->next = a;

    return a;
}