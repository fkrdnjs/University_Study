#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int front = 0;
int rear = 0;

void print(int* queue, int size) {

    int i;

    for (i = 0; i < size; i++)
        printf(" %d", queue[i]);

    printf("\n");
}

void enqueue(int* queue, int size, int elem) {

    if ((rear + 1) % size == front % size) {
        printf("overflow");
        print(queue, size);

        free(queue);

        exit(1);
    }
    else {
        rear = (rear + 1) % size;
        queue[rear % size] = elem;
    }
}

void dequeue(int* queue, int size) {

    if (rear % size == front % size) {
        printf("under flow");

        free(queue);

        exit(1);
    }
    else {
        front = (front + 1) % size;
        queue[front % size] = 0;
    }
}

int main(void)
{
    int q, n;
    int i, elem;
    int* queue;
    char command;

    scanf("%d", &q);

    queue = (int*)malloc(sizeof(int) * q);
    if (queue == NULL)
        return -1;

    for (i = 0; i < q; i++)
        queue[i] = 0;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        getchar();
        scanf("%c", &command);

        if (command == 'I') {
            scanf("%d", &elem);
            enqueue(queue, q, elem);
        }
        else if (command == 'D') {
            dequeue(queue, q);
        }
        else if (command == 'P') {
            print(queue, q);
        }
    }

    free(queue);

    return 0;
}
