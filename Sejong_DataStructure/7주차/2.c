#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct NODE {

    int coef;
    int exp;
    struct NODE* next;

}node;

void appendTerm(node* header, int c, int e) {                               //마지막에 추가하는 함수

    node* new;

    new = (node*)malloc(sizeof(node));                                     //새로운 노드 선언
    if (new == NULL)
        return -1;

    new->coef = c;                                                         //새로운 노드 초기화 -> 제일 끝 노드로 초기화 
    new->exp = e;
    new->next = NULL;

    while (1) {                                                             //제일 끝으로 이동
        if (header->next == NULL)
            break;
        header = header->next;
    }

    header->next = new;                                                     //제일 끝 노드에 연결
}

node* addPoly(node* x, node* y) {                                           //더하는 함수

    node* first, * second;
    node* result;
    int sum = 0;

    first = x->next;                                                        //제일 처음 노드의 다음걸로 초기화
    second = y->next;

    result = (node*)malloc(sizeof(node));
    if (result == NULL)
        return -1;

    result->next = NULL;

    while (first && second) {
        if (first->exp > second->exp) {                                     //첫 번째 식의 차수가 더 클 경우 첫 번째 식을 더하고 다음 항으로 이동시킴
            appendTerm(result, first->coef, first->exp);
            first = first->next;
        }

        else if (first->exp < second->exp) {                                //두 번째 식의 차수가 더 클 경우
            appendTerm(result, second->coef, second->exp);
            second = second->next;
        }

        else {                                                                 //같으면
            sum = first->coef + second->coef;

            if (sum != 0)                                                       //더했을 때 사라지지 않으면 더해주기
                appendTerm(result, sum, first->exp);

            first = first->next;                                                //첫 번째 식이랑 두 번째 식 모두 다음 항으로 이동
            second = second->next;
        }
    }
    //반복문 탈출하고 남은 항이 있을 경우 모두 더해주기
    while (first) {
        appendTerm(result, first->coef, first->exp);
        first = first->next;
    }

    while (second) {
        appendTerm(result, second->coef, second->exp);
        second = second->next;
    }

    return result;

}

void freehelp(node* header) {                                                   //프리해주는 함수

    node* del = header;

    while (1) {
        del = header;
        header = header->next;

        free(del);

        if (header->next == NULL) {
            free(header);
            break;
        }
    }
}

int main(void) {

    int n, i;
    int a, b;
    node* first, * second;
    node* result, * k;

    first = (node*)malloc(sizeof(node));
    if (first == NULL)
        return -1;

    second = (node*)malloc(sizeof(node));
    if (second == NULL)
        return -1;

    first->next = NULL;                                                 //식 두개 널로 초기화
    second->next = NULL;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {                                           //첫 번째 식 입력
        scanf("%d", &a);
        scanf("%d", &b);
        appendTerm(first, a, b);
    }

    scanf("%d", &n);

    for (i = 0; i < n; i++) {                                               //두 번째 식 입력
        scanf("%d", &a);
        scanf("%d", &b);
        appendTerm(second, a, b);
    }

    result = addPoly(first, second);                                    //식 두개 더하기

    k = result->next;

    while (k) {                                                         //출력
        printf(" %d %d", k->coef, k->exp);
        k = k->next;
    }

    freehelp(result);                                                   //처음 식 두개랑 결과식 프리
    freehelp(first);
    freehelp(second);

    return 0;
}