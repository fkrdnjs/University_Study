#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)

int* x;
int M;

int h(int k);
void initBucketArray();
int getNextBucket(int v, int i);
void insertItem(int k);
int findElement(int k);

int main() {

    int n;
    char command;
    int k, res;

    scanf("%d %d", &M, &n);
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

            insertItem(k);
        }
        else if (command == 's') {
            scanf("%d", &k);
            getchar();

            res = findElement(k);

            if (res == -1)
                printf("-1\n");
            else
                printf("%d %d\n", res, k);
        }

        else if (command == 'e') {
            free(x);
            break;
        }
    }

    return 0;
}

int h(int k) {
    return k % M;
}

void initBucketArray() {

    int i;

    for (i = 0; i < M; i++) {
        x[i] = 0;
    }
}

int getNextBucket(int v, int i) {
    return (v + i) % M;
}

void insertItem(int k) {

    int index;
    int i;

    for (i = 0; i < M; i++) {

        index = getNextBucket(h(k), i);

        if (x[index] == 0) {

            x[index] = k;
            printf("%d\n", index);

            return;
        }
        else
            printf("C");
    }
}

int findElement(int k) {

    int index;
    int i;

    for (i = 0; i < M; i++) {

        index = getNextBucket(h(k), i);

        if (x[index] == k)
            return index;

    }

    return -1;
}