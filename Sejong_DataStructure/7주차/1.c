#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct NODE {

    int elem;
    struct NODE* next;

}node;

void add(node* x, int e) {

    node* new;
    node* p;

    new = (node*)malloc(sizeof(node));
    if (new == NULL)
        return -1;

    new->elem = e;
    new->next = NULL;

    p = x;

    while (1) {
        if (p->next == NULL)
            break;
        p = p->next;
    }

    p->next = new;

}

node* unions(node* x, node* y) {

    node* first = x;
    node* second = y;
    node* sum;

    sum = (node*)malloc(sizeof(node));
    if (sum == NULL)
        return -1;

    sum->next = NULL;
    sum->elem = NULL;

    if (first->next == NULL && second->next == NULL)
        return sum;

    else if (first->next == NULL) {
        free(sum);
        return second;
    }

    else if (second->next == NULL) {
        free(sum);
        return first;
    }

    else {
        while (first != NULL && second != NULL) {
            if (first->elem < second->elem) {
                add(sum, first->elem);
                first = first->next;
            }
            else if (first->elem > second->elem) {
                add(sum, second->elem);
                second = second->next;
            }
            else if (first->elem == second->elem) {
                if (first->elem == NULL) {
                    first = first->next;
                    second = second->next;
                    continue;
                }
                add(sum, first->elem);
                first = first->next;
                second = second->next;
            }
        }

        while (first != NULL) {
            add(sum, first->elem);
            first = first->next;
        }

        while (second != NULL) {
            add(sum, second->elem);
            second = second->next;
        }
    }

    return sum;

}

node* intersect(node* x, node* y) {

    node* first = x;
    node* second = y;
    node* sum;

    sum = (node*)malloc(sizeof(node));
    if (sum == NULL)
        return -1;

    sum->next = NULL;
    sum->elem = NULL;

    if (first->next == NULL || second->next == NULL)
        return sum;

    else {
        while (first != NULL && second != NULL) {
            if (first->elem < second->elem) {
                first = first->next;
            }
            else if (first->elem > second->elem) {
                second = second->next;
            }
            else if (first->elem == second->elem) {
                if (first->elem == NULL) {
                    first = first->next;
                    second = second->next;
                    continue;
                }

                add(sum, first->elem);
                first = first->next;
                second = second->next;
            }
        }
    }

    return sum;

}

void printhelp(node* x) {

    node* p = x->next;

    if (p == NULL)
        printf("0\n");
    else {
        while (1) {
            if (p == NULL)
                break;
            printf(" %d", p->elem);
            p = p->next;
        }
        printf("\n");
    }
}

void freehelp(node* x) {

    node* del = x;

    while (1) {
        del = x;
        x = x->next;

        free(del);

        if (x == NULL) {
            free(x);
            break;
        }
    }
}

int main(void) {

    int x, y, i, e;
    int result;
    node* a;
    node* b;
    node* unionset, * sumset;

    a = (node*)malloc(sizeof(node));
    if (a == NULL)
        return -1;

    b = (node*)malloc(sizeof(node));
    if (b == NULL)
        return -1;

    a->next = NULL;
    b->next = NULL;
    a->elem = NULL;
    b->elem = NULL;

    scanf("%d", &x);

    for (i = 0; i < x; i++) {
        scanf("%d", &e);
        add(a, e);
    }

    scanf("%d", &y);

    for (i = 0; i < y; i++) {
        scanf("%d", &e);
        add(b, e);
    }

    unionset = unions(a, b);
    sumset = intersect(a, b);

    printhelp(unionset);
    printhelp(sumset);

    if (unionset != a && unionset != b)
        freehelp(unionset);
    freehelp(a);
    freehelp(b);
    freehelp(sumset);

    return 0;
}

/*
6
3 7 45 88 99 101
4
7 10 15 45
*/