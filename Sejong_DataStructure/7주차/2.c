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

void appendTerm(node* header, int c, int e) {                               //�������� �߰��ϴ� �Լ�

    node* new;

    new = (node*)malloc(sizeof(node));                                     //���ο� ��� ����
    if (new == NULL)
        return -1;

    new->coef = c;                                                         //���ο� ��� �ʱ�ȭ -> ���� �� ���� �ʱ�ȭ 
    new->exp = e;
    new->next = NULL;

    while (1) {                                                             //���� ������ �̵�
        if (header->next == NULL)
            break;
        header = header->next;
    }

    header->next = new;                                                     //���� �� ��忡 ����
}

node* addPoly(node* x, node* y) {                                           //���ϴ� �Լ�

    node* first, * second;
    node* result;
    int sum = 0;

    first = x->next;                                                        //���� ó�� ����� �����ɷ� �ʱ�ȭ
    second = y->next;

    result = (node*)malloc(sizeof(node));
    if (result == NULL)
        return -1;

    result->next = NULL;

    while (first && second) {
        if (first->exp > second->exp) {                                     //ù ��° ���� ������ �� Ŭ ��� ù ��° ���� ���ϰ� ���� ������ �̵���Ŵ
            appendTerm(result, first->coef, first->exp);
            first = first->next;
        }

        else if (first->exp < second->exp) {                                //�� ��° ���� ������ �� Ŭ ���
            appendTerm(result, second->coef, second->exp);
            second = second->next;
        }

        else {                                                                 //������
            sum = first->coef + second->coef;

            if (sum != 0)                                                       //������ �� ������� ������ �����ֱ�
                appendTerm(result, sum, first->exp);

            first = first->next;                                                //ù ��° ���̶� �� ��° �� ��� ���� ������ �̵�
            second = second->next;
        }
    }
    //�ݺ��� Ż���ϰ� ���� ���� ���� ��� ��� �����ֱ�
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

void freehelp(node* header) {                                                   //�������ִ� �Լ�

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

    first->next = NULL;                                                 //�� �ΰ� �η� �ʱ�ȭ
    second->next = NULL;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {                                           //ù ��° �� �Է�
        scanf("%d", &a);
        scanf("%d", &b);
        appendTerm(first, a, b);
    }

    scanf("%d", &n);

    for (i = 0; i < n; i++) {                                               //�� ��° �� �Է�
        scanf("%d", &a);
        scanf("%d", &b);
        appendTerm(second, a, b);
    }

    result = addPoly(first, second);                                    //�� �ΰ� ���ϱ�

    k = result->next;

    while (k) {                                                         //���
        printf(" %d %d", k->coef, k->exp);
        k = k->next;
    }

    freehelp(result);                                                   //ó�� �� �ΰ��� ����� ����
    freehelp(first);
    freehelp(second);

    return 0;
}