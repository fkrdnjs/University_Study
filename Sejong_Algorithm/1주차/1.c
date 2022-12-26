#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
    char elem;
    struct node* prev;
    struct node* next;
}node;

int cnt = 2;

void add(node* header, int rank, char el) {

    if (rank < 1 || rank >= cnt) {      //�ùٸ��� ���� ������ ����ó��
        printf("invalid position\n");
        return 0;
    }

    int i;
    node* new, * p = header;

    new = (node*)malloc(sizeof(node));  //���ο� ��� �Ҵ�
    if (new == NULL)
        return -1;

    new->elem = el;                     //���ο� ����� elem �� ����

    for (i = 0; i < rank; i++)          //������ ������ŭ �̵�
        p = p->next;

    p->prev->next = new;                //��� ����
    new->prev = p->prev;
    new->next = p;
    p->prev = new;

    cnt += 1;                           //��� ���� 1 ����

}

void delete(node* header, int rank) {

    if (rank < 1 || rank > cnt - 2) {   //�ùٸ��� ���� ������ ����ó��
        printf("invalid position\n");
        return 0;
    }

    node* p = header;
    int i;

    for (i = 0; i < rank; i++)          //������ ������ŭ �̵�
        p = p->next;

    p->prev->next = p->next;            //��� ����
    p->next->prev = p->prev;

    cnt -= 1;                           //��� ���� 1 ����

    free(p);                            //������ ��� ����
}

char get(node* header, int rank) {

    if (rank < 1 || rank > cnt - 2) {   //�ùٸ��� ���� ������ ����ó��
        printf("invalid position\n");
        return '0';
    }

    int i;
    node* p = header;

    for (i = 0; i < rank; i++)          //��� �̵�
        p = p->next;

    return p->elem;                     //��� ������ ��ȯ

}

void print(node* header) {

    if (cnt - 2 <= 0) {                 //�ùٸ��� ���� ������ ����ó��
        printf("invalid position\n");
        return 0;
    }

    node* p = header;

    for (p = p->next; p->next != NULL; p = p->next) //NULL�� �ƴ� ���� ����Ʈ
        printf("%c", p->elem);

    printf("\n");
}

int main() {

    int n, i, rank;
    char command, el, k;
    node* header, * trailer;

    header = (node*)malloc(sizeof(node));           //header, trailer �Ҵ�
    if (header == NULL)
        return -1;

    trailer = (node*)malloc(sizeof(node));
    if (trailer == NULL)
        return -1;

    header->prev = NULL;                            //header, trailer ����
    header->next = trailer;

    trailer->prev = header;
    trailer->next = NULL;

    scanf("%d", &n);
    getchar();

    for (i = 0; i < n; i++) {                   //command�� ���� �Լ� ȣ��
        scanf("%c", &command);
        getchar();

        if (command == 'A') {
            scanf("%d", &rank);
            getchar();

            scanf("%c", &el);
            getchar();

            add(header, rank, el);

        }
        else if (command == 'D') {
            scanf("%d", &rank);
            getchar();

            delete(header, rank);
        }
        else if (command == 'G') {
            scanf("%d", &rank);
            getchar();

            k = get(header, rank);

            if (k != '0')
                printf("%c\n", k);
        }
        else if (command == 'P') {
            print(header);
        }
    }

    node* del;

    del = header;

    while (1) {                     //free ����
        del = header;
        header = header->next;

        free(del);

        if (header->next == NULL) {
            free(header);
            break;
        }
    }

    return 0;
}