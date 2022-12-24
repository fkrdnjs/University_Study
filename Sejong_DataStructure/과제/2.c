#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct NODE {                           //노드 구조체 선언

    int elem;
    char name;
    struct NODE* enext;                         //요소넥스트 : 가로로 이동하는 넥스트
    struct NODE* gnext;                         //그룹넥스트 : 상하로 이동하는 넥스트

}node;

typedef struct groups {                         //그룹 구조체 선언
    node* header;
}g;

typedef struct elements {                       //쿠폰 구조체 선언
    node* header;
}e;

g group[5];                                     //전역변수로 그룹 배열, 쿠폰 배열, 갯수 선언
e element[4];

int ne = 4;
int ng = 5;

void initShare() {                              //초기화 함수

    int i;
    node* h;

    for (i = 0; i < ne; i++) {                  //쿠폰 배열의 헤더 초기화
        h = (node*)malloc(sizeof(node));        //새로운 노드 선언
        if (h == NULL)
            return -1;

        h->gnext = h;                           //새로운 노드의 그룹넥스트가 자신을 가리키도록 초기화
        element[i].header = h;                  //쿠폰 배열의 헤더에 새로운 노드 대입
    }

    for (i = 0; i < ng; i++) {                  //그룹 배열의 헤더 초기화
        h = (node*)malloc(sizeof(node));
        if (h == NULL)
            return -1;

        h->enext = h;
        group[i].header = h;                    //그룹 배열의 헤더에 새로운 노드 대입
    }

}

void addShare(int el, char na) {                //그룹, 쿠폰명에 맞게 추가하는 함수

    node* new;
    node* hg, * he;
    node* p;

    hg = group[na - 'A'].header;                //hg를 그룹배열의 헤더로 초기화
    p = hg->enext;                              //p를 헤더의 요소넥스트로 초기화

    while (1) {

        if (p == hg)                            //p가 다시 헤더로 돌아올 경우 끝냄
            break;

        else if (p->elem == el) {               //중복되는 경우가 있을 때
            printf("Duplicate\n");              //duplicate 출력하고 함수 종료시킴
            return -1;
        }

        p = p->enext;
    }
    // 중복되는 경우 없을 때 추가시킴
    new = (node*)malloc(sizeof(node));          //새로운 노드 선언
    if (new == NULL)
        return -1;

    hg = group[na - 'A'].header;                //hg를 해당 그룹 배열의 헤더로 초기화
    new->enext = hg->enext;                     //새로운 노드는 무조건 헤드 다음에 넣는 방법
    hg->enext = new;

    he = element[el - 1].header;                //he를 해당 쿠폰 배열의 헤더로 초기화
    new->gnext = he->gnext;                     //마찬가지로 헤드 다음에 넣음
    he->gnext = new;

    new->elem = el;                             //노드에 이름, 쿠폰명 넣어줌
    new->name = na;

    printf("OK\n");

}

void removeShare(int el, char na) {             //제거하는 함수

    node* p;
    node* hg, * he;
    node* k;

    hg = group[na - 'A'].header;
    k = hg->enext;

    while (1) {

        if (k == hg) {                          //제거할 노드가 없을 경우 함수 끝냄
            printf("NO Match\n");
            return -1;
        }

        if (k->elem == el)                      //제거할 노드 있으면 계속 진행
            break;

        k = k->enext;
    }

    hg = group[na - 'A'].header;                //hg를 그룹 배열의 헤더로 초기화

    while (1) {
        if (hg->enext->elem == el) {            //prev가 없기 때문에 hg 넥스트의 쿠폰이 같으면 종료시킴
            p = hg->enext;                      //p에는 제거할 노드 저장
            break;
        }
        hg = hg->enext;
    }

    hg->enext = p->enext;                       //hg의 요소넥스트가 제거할 노드의 넥스트 가리키도록 함

    he = element[el - 1].header;                //쿠폰 배열에서도 위와 마찬가지

    while (1) {
        if (he->gnext->name == na) {            //위치 찾고
            p = he->gnext;
            break;
        }
        he = he->gnext;
    }

    he->gnext = p->gnext;                       //he의 쿠폰 넥스트가 제거할 노드의 넥스트

    printf("OK\n");

    free(p);                                    //제거할 노드 프리해줌

}

void traverseShareElements(char k) {            //사람의 쿠폰 출력할 함수

    node* h;
    node* p;

    h = group[k - 'A'].header;                  //해당 사람의 헤더로 초기화
    p = h->enext;                               //p를 h의 요소넥스트로 초기화

    if (p == h) {                               //출력할 요소가 하나도 없으면 0출력 후 끝냄
        printf("0\n");
        return -1;
    }

    while (p != h) {                            //다시 헤더로 올 때까지 쿠폰 출력
        printf("%d ", p->elem);
        p = p->enext;
    }

    printf("\n");
}

void traverseShareGroups(int k) {               //사람 출력할 함수

    node* h;
    node* p;

    h = element[k - 1].header;                  //해당 쿠폰의 헤더로 초기화
    p = h->gnext;

    if (p == h) {                               //쿠폰 가진 사람 없으면 0출력 후 끝냄
        printf("0\n");
        return -1;
    }

    while (p != h) {                            //다시 헤더로 올 때까지 이름 출력
        printf("%c ", p->name);
        p = p->gnext;
    }

    printf("\n");
}

void pexit() {                                  //프리해주는 함수

    node* he, * p, * hg, * del;
    int i;

    for (i = 0; i < ne; i++) {                  //쿠폰 배열 프리해주는 부분
        he = element[i].header;                 //헤더로 초기화
        p = he->gnext;                          //헤더의 넥스트로 초기화

        while (1) {

            if (p == he)                        //다시 헤더로 돌아오면 프리하지 않고 탈출
                break;

            del = p;
            p = p->gnext;

            free(del);                          //추가한 노드들 프리

        }

        free(he);                               //쿠폰 배열의 헤더 프리
    }

    for (i = 0; i < ng; i++) {
        hg = group[i].header;                   //그룹 배열의 헤더로 초기화

        free(hg);                               //그룹 배열의 헤더 프리
    }

}

int main(void) {

    int i, e;
    char cmd, g;
    int flag = 0;

    initShare();                                //초기화 하는 함수 호출

    while (1) {

        scanf("%c", &cmd);                      //커맨드 입력
        getchar();

        switch (cmd) {
        case 'a':                           //a일 경우
            scanf("%d", &e);
            getchar();

            scanf("%c", &g);
            getchar();

            addShare(e, g);                 //addShare 호출
            break;

        case 'r':                           //r일 경우
            scanf("%d", &e);
            getchar();

            scanf("%c", &g);
            getchar();

            removeShare(e, g);              //removeShare 호출
            break;

        case 'e':                           //e일 경우
            scanf("%c", &g);
            getchar();

            traverseShareElements(g);       //traverseShareElements 호출
            break;

        case 'g':                           //g일 경우
            scanf("%d", &e);
            getchar();

            traverseShareGroups(e);         //traverseShareGroups 호출
            break;

        default:                            //그 외일 경우
            pexit();                        //전부 프리 후
            flag = 1;                       //플래그 변수 1로 만들고 끝
            break;

        }

        if (flag == 1)                          //플래그 변수 1이면 while문 탈출하고 종료
            break;
    }

    return 0;
}