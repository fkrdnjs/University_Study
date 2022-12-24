#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct queue {
    int elem;
    struct queue* prev;
    struct queue* next;
}node;

node* front, * rear;
int size = 0;

void add_front(node* deque, int x) {

    node* new;

    new = (node*)malloc(sizeof(node));
    if (new == NULL)
        return -1;

    if (size == 0) {
        new->elem = x;
        new->next = NULL;
        new->prev = NULL;

        front = new;
        rear = new;
    }
    else {
        new->elem = x;
        new->prev = NULL;
        new->next = front;

        deque->prev = new;
        front = new;
    }

    size += 1;

}

void add_rear(node* deque, int x) {

    node* new;

    new = (node*)malloc(sizeof(node));
    if (new == NULL)
        return -1;

    if (size == 0) {
        new->elem = x;
        new->next = NULL;
        new->prev = NULL;

        front = new;
        rear = new;
    }
    else {
        new->elem = x;
        new->prev = deque;
        new->next = NULL;

        deque->next = new;
        rear = new;
    }

    size += 1;

}

int delete_front(node* deque) {

    node* p = deque;
    int result;

    if (size == 0) {
        printf("underflow\n");
        exit(1);
    }
    else {
        result = deque->elem;

        if (size == 1)
            free(p);
        else {
            front = front->next;
            front->prev = NULL;
            free(p);
        }

        size -= 1;
    }

    if (size == 0) {
        front = NULL;
        rear = NULL;
    }

    return result;

}

int delete_rear(node* deque) {

    node* p = deque;
    int result;

    if (size == 0) {
        printf("underflow\n");
        exit(1);
    }
    else {
        result = deque->elem;

        if (size == 1)
            free(p);
        else {
            rear = rear->prev;
            rear->next = NULL;
            free(p);
        }
        size -= 1;
    }

    if (size == 0) {
        front = NULL;
        rear = NULL;
    }

    return result;

}

void print(node* deque) {

    node* p = deque;

    while (p != NULL) {
        printf(" %d", p->elem);
        p = p->next;
    }
    printf("\n");
}

void freehelp() {

    node* del = front;

    while (del != NULL) {
        front = front->next;
        free(del);
        del = front;
    }

}

int main(void)
{
    int n, k;
    char command[3];
    int elem, i;

    scanf("%d", &n);
    getchar();

    front = NULL;
    rear = NULL;

    for (i = 0; i < n; i++) {
        scanf("%s", command);
        getchar();

        if (strcmp(command, "AF") == 0) {
            scanf("%d", &elem);
            getchar();

            add_front(front, elem);
        }
        else if (strcmp(command, "AR") == 0) {
            scanf("%d", &elem);
            getchar();

            add_rear(rear, elem);
        }
        else if (strcmp(command, "DF") == 0) {
            k = delete_front(front);
        }
        else if (strcmp(command, "DR") == 0) {
            k = delete_rear(rear);
        }
        else if (strcmp(command, "P") == 0) {
            print(front);
        }
    }

    freehelp();

    return 0;
}
