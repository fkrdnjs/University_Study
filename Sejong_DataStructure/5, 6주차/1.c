#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int cnt = 2; //연결리스트 총 갯수 세는 전역변수

typedef struct NODE {

    char elem;
    struct NODE* prev;
    struct NODE* next;

}node;

void add(node* header, int rank, char e) {

    if (rank < 1 || rank >= cnt) { //조건에 맞는지부터 먼저 확인
        printf("invalid position\n");
        return 0;
    }

    node* p, * new;
    int i;

    new = (node*)malloc(sizeof(node));
    if (new == NULL)
        return -1;

    new->elem = e;

    p = header;

    for (i = 1; i <= rank; i++) {
        p = p->next;
    }

    new->prev = p->prev;
    new->next = p;
    p->prev->next = new;
    p->prev = new;

    cnt += 1;

}

void delete(node* header, int rank) {

    if (rank < 1 || rank > cnt - 2) {
        printf("invalid position\n");
        return 0;
    }

    node* p;
    int i;

    p = header;

    for (i = 1; i <= rank; i++)
        p = p->next;

    p->prev->next = p->next;
    p->next->prev = p->prev;

    cnt -= 1;

    free(p);

}

char get(node* header, int rank) {

    if (rank < 1 || rank > cnt - 2) {
        printf("invalid position\n");
        return '0';
    }

    node* p;
    int i;

    p = header;

    for (i = 1; i <= rank; i++)
        p = p->next;

    return p->elem;

}

void print(node* header) {

    if (cnt - 2 <= 0) {
        printf("invalid position\n");
        return 0;
    }

    node* p = header;

    for (p = p->next; p->next != NULL; p = p->next)
        printf("%c", p->elem);

    printf("\n");

}

int main() {

    int n;
    int i, rank;
    char command, e, x;
    node* header, * trailer, * k, * del;

    //헤더랑 트레일러 노드 선언 후 초기화
    header = (node*)malloc(sizeof(node));
    if (header == NULL)
        return -1;

    trailer = (node*)malloc(sizeof(node));
    if (trailer == NULL)
        return -1;

    header->next = trailer;
    header->prev = NULL;

    trailer->prev = header;
    trailer->next = NULL;

    scanf("%d", &n);
    getchar();

    for (i = 0; i < n; i++) {
        scanf("%c", &command);
        getchar();

        if (command == 'A') {
            scanf("%d", &rank);
            getchar();

            scanf("%c", &e);
            getchar();

            add(header, rank, e);

        }
        else if (command == 'D') {
            scanf("%d", &rank);
            getchar();

            delete(header, rank);
        }
        else if (command == 'G') {
            scanf("%d", &rank);
            getchar();

            x = get(header, rank);

            if (x != '0')
                printf("%c\n", x);
        }
        else if (command == 'P') {
            print(header);
        }

    }

    k = header;
    del = header;

    while (1) {
        del = k;
        k = k->next;

        free(del);

        if (k->next == NULL) {
            free(k);
            break;
        }
    }


    return 0;
}