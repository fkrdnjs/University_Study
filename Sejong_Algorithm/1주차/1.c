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

    if (rank < 1 || rank >= cnt) {      //올바르지 않은 순위면 예외처리
        printf("invalid position\n");
        return 0;
    }

    int i;
    node* new, * p = header;

    new = (node*)malloc(sizeof(node));  //새로운 노드 할당
    if (new == NULL)
        return -1;

    new->elem = el;                     //새로운 노드의 elem 값 대입

    for (i = 0; i < rank; i++)          //삽입할 순서만큼 이동
        p = p->next;

    p->prev->next = new;                //노드 연결
    new->prev = p->prev;
    new->next = p;
    p->prev = new;

    cnt += 1;                           //노드 갯수 1 증가

}

void delete(node* header, int rank) {

    if (rank < 1 || rank > cnt - 2) {   //올바르지 않은 순위면 예외처리
        printf("invalid position\n");
        return 0;
    }

    node* p = header;
    int i;

    for (i = 0; i < rank; i++)          //삭제할 순위만큼 이동
        p = p->next;

    p->prev->next = p->next;            //노드 연결
    p->next->prev = p->prev;

    cnt -= 1;                           //노드 갯수 1 감소

    free(p);                            //삭제할 노드 프리
}

char get(node* header, int rank) {

    if (rank < 1 || rank > cnt - 2) {   //올바르지 않은 순위면 예외처리
        printf("invalid position\n");
        return '0';
    }

    int i;
    node* p = header;

    for (i = 0; i < rank; i++)          //노드 이동
        p = p->next;

    return p->elem;                     //노드 데이터 반환

}

void print(node* header) {

    if (cnt - 2 <= 0) {                 //올바르지 않은 순위면 예외처리
        printf("invalid position\n");
        return 0;
    }

    node* p = header;

    for (p = p->next; p->next != NULL; p = p->next) //NULL이 아닌 동안 프린트
        printf("%c", p->elem);

    printf("\n");
}

int main() {

    int n, i, rank;
    char command, el, k;
    node* header, * trailer;

    header = (node*)malloc(sizeof(node));           //header, trailer 할당
    if (header == NULL)
        return -1;

    trailer = (node*)malloc(sizeof(node));
    if (trailer == NULL)
        return -1;

    header->prev = NULL;                            //header, trailer 연결
    header->next = trailer;

    trailer->prev = header;
    trailer->next = NULL;

    scanf("%d", &n);
    getchar();

    for (i = 0; i < n; i++) {                   //command에 따른 함수 호출
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

    while (1) {                     //free 과정
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