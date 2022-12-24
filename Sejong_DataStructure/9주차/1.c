#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int top = -1;
int size;

void push(char* stack, char k) {

    if (top == size - 1) {
        printf("Stack FULL\n");
        return -1;
    }

    top += 1;
    stack[top] = k;
}

char pop(char* stack) {

    if (top == -1) {
        printf("Stack Empty\n");
        return -1;
    }

    top -= 1;
    return stack[top + 1];

}

void peek(char* stack) {

    if (top == -1) {
        printf("Stack Empty\n");
        return -1;
    }

    printf("%c\n", stack[top]);
}

void duplicate(char* stack) {

    char result;

    if (top >= size) {
        printf("Stack FULL");
        return -1;
    }

    result = pop(stack);

    push(stack, result);
    push(stack, result);
}

void upRotate(char* stack, int n) {

    if (n > top + 1)
        return -1;

    char* tmp;
    int i;

    tmp = (char*)malloc(sizeof(char) * n);
    if (tmp == NULL)
        return -1;

    for (i = 0; i < n; i++)
        tmp[i] = pop(stack);

    push(stack, tmp[0]);

    for (i = n - 1; i > 0; i--)
        push(stack, tmp[i]);

    free(tmp);

}

void downRotate(char* stack, int n) {

    if (n > top + 1)
        return -1;

    char* tmp;
    int i;

    tmp = (char*)malloc(sizeof(char) * n);
    if (tmp == NULL)
        return -1;

    for (i = 0; i < n; i++)
        tmp[i] = pop(stack);

    for (i = n - 2; i >= 0; i--)
        push(stack, tmp[i]);

    push(stack, tmp[n - 1]);

    free(tmp);

}

void print(char* stack) {

    int i;

    for (i = top; i >= 0; i--)
        printf("%c", stack[i]);
    printf("\n");
}

int main(void)
{
    int n;
    char* stack;
    char com[6], k;
    int i, j, num;

    scanf("%d", &size);
    scanf("%d", &n);

    stack = (char*)malloc(sizeof(char) * size);
    if (stack == NULL)
        return -1;

    for (i = 0; i < size; i++)
        stack[i] = '\0';

    for (i = 0; i < n; i++) {
        scanf("%s", com);
        getchar();

        if (strcmp(com, "PUSH") == 0) {
            scanf("%c", &k);
            getchar();
            push(stack, k);
        }

        else if (strcmp(com, "POP") == 0)
            pop(stack);

        else if (strcmp(com, "PEEK") == 0)
            peek(stack);

        else if (strcmp(com, "DUP") == 0)
            duplicate(stack);

        else if (strcmp(com, "UpR") == 0) {
            scanf("%d", &num);
            getchar();
            upRotate(stack, num);
        }

        else if (strcmp(com, "DownR") == 0) {
            scanf("%d", &num);
            getchar();
            downRotate(stack, num);
        }

        else if (strcmp(com, "PRINT") == 0)
            print(stack);
    }

    free(stack);

    return 0;
}
