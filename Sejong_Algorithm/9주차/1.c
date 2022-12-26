#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)

typedef struct node {
    int elem;
    struct node* next;
}node;

int M;
node** bucket;

node* getnode(int elem);
int h(int x);
void initBucketArray();
void insertItem(int x);
int findElement(int x);
int removeElement(int x);
void printBucketArray();
void freehelp();

int main(void) {
    char command;
    int x;

    scanf("%d", &M);
    getchar();

    bucket = (node**)malloc(sizeof(node*) * M);
    if (bucket == NULL)
        return -1;

    initBucketArray();

    while (1) {
        scanf("%c", &command);

        if (command == 'i') {
            scanf("%d", &x);
            getchar();
            insertItem(x);
        }

        else if (command == 's') {
            scanf("%d", &x);
            getchar();
            printf("%d\n", findElement(x));
        }

        else if (command == 'd') {
            scanf("%d", &x);
            getchar();
            printf("%d\n", removeElement(x));
        }
        else if (command == 'p')
            printBucketArray();

        else if (command == 'e')
            break;

    }

    freehelp();

    return 0;
}

node* getnode(int elem) {
    node* new;

    new = (node*)malloc(sizeof(node));
    new->next = NULL;
    new->elem = elem;

    return new;
}

int h(int x) {
    return x % M;
}

void initBucketArray() {

    int i;

    for (i = 0; i < M; i++) {
        bucket[i] = NULL;
    }
}

void insertItem(int x) {

    node* new = getnode(x);
    node* tmp;

    int v = h(x);

    if (bucket[v] == NULL)
        bucket[v] = new;

    else {
        tmp = bucket[v];
        bucket[v] = new;
        new->next = tmp;
    }

}

int findElement(int x) {

    node* k;
    int v = h(x);
    int cnt = 0;

    if (bucket[v] == NULL)
        return 0;

    k = bucket[v];

    while (k != NULL) {
        cnt++;

        if (k->elem == x)
            return cnt;

        k = k->next;
    }

    return 0;
}

int removeElement(int x) {

    node* k, * del, * a;
    int v = h(x);
    int cnt = findElement(x);
    int i;

    if (cnt == 0)
        return 0;

    k = bucket[v];
    a = bucket[v];
    del = bucket[v];

    for (i = 1; i < cnt; i++) {

        if (i == cnt - 2)
            a = k;

        k = k->next;
    }

    del = k;

    if (del->next == NULL) {
        if (bucket[v] == del)
            bucket[v] = NULL;
        else
            a->next = NULL;
    }

    else {
        if (bucket[v] == del)
            bucket[v] = del->next;
        else
            a->next = del->next;
    }

    free(del);

    return cnt;

}

void printBucketArray() {

    node* k;
    int i;

    for (i = 0; i < M; i++) {
        if (bucket[i] == NULL)
            continue;

        k = bucket[i];

        while (k != NULL) {
            printf(" %d", k->elem);
            k = k->next;
        }
    }
    printf("\n");
}

void freehelp() {

    node* k, * next;
    int i;

    for (i = 0; i < M; i++) {
        if (bucket[i] == NULL)
            continue;

        k = bucket[i];

        while (k != NULL) {
            next = k->next;
            free(k);
            k = next;
        }
    }

    free(bucket);

}