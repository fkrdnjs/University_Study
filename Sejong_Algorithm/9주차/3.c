#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)

int* x;
int M;

int h(int k);
int h2(int k, int q);
void initBucketArray();
int getNextBucket(int k, int i, int q);
void insertItem(int k, int q);
int findElement(int k, int q);
void printItem();

int main() {

    char command;
    int n, q;
    int i, k;
    int res;

    scanf("%d %d %d", &M, &n, &q);
    getchar();

    x = (int*)malloc(sizeof(int) * M);
    if (x == NULL)
        return -1;

    initBucketArray();

    while (1) {
        scanf("%c", &command);

        if (command == 'i') {
            scanf("%d", &k);
            getchar();

            insertItem(k, q);
        }
        else if (command == 's') {
            scanf("%d", &k);
            getchar();

            res = findElement(k, q);

            if (res == -1)
                printf("-1\n");
            else
                printf("%d %d\n", res, k);

        }
        else if (command == 'p')
            printItem();

        else if (command == 'e') {

            printItem();
            free(x);

            break;
        }

    }

    return 0;
}

int h(int k) {
    return k % M;
}

int h2(int k, int q) {
    return q - (k % q);
}

void initBucketArray() {

    int i;

    for (i = 0; i < M; i++) {
        x[i] = 0;
    }
}

int getNextBucket(int i, int k, int q) {
    return (h(k) + i * h2(k, q)) % M;
}

void insertItem(int k, int q) {

    int index;
    int i;

    for (i = 0; i < M; i++) {

        index = getNextBucket(i, k, q);

        if (x[index] == 0) {

            x[index] = k;
            printf("%d\n", index);

            return;
        }
        else
            printf("C");
    }
}

int findElement(int k, int q) {

    int index;
    int i;

    for (i = 0; i < M; i++) {

        index = getNextBucket(i, k, q);

        if (x[index] == k)
            return index;

    }

    return -1;
}

void printItem() {

    int i;

    for (i = 0; i < M; i++)
        printf(" %d", x[i]);

    printf("\n");
}