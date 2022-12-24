#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int top = -1;
int size = 1000;

void push(char* stack, char k) {

    if (top == size) {
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

int isBalanced(char* sentence, char* stack) {

    char k;
    int i, len;

    len = strlen(sentence);

    for (i = 0; i < len; i++) {
        if (sentence[i] == '(' || sentence[i] == '{' || sentence[i] == '[') {
            push(stack, sentence[i]);
        }
        else if (sentence[i] == ')' || sentence[i] == '}' || sentence[i] == ']') {
            if (top == -1)
                return 0;

            k = pop(stack);

            if (sentence[i] == ')') {
                if (k != '(')
                    return 0;
            }

            else if (sentence[i] == '}') {
                if (k != '{')
                    return 0;
            }

            else if (sentence[i] == ']') {
                if (k != '[')
                    return 0;
            }
        }
    }

    if (top == -1)
        return 1;
    else
        return 0;
}

int main(void)
{
    char stack[1000] = { '\0' };
    char sentence[1000];
    int cnt = 0;
    int i, len, result;

    gets(sentence);
    len = strlen(sentence);

    for (i = 0; i < len; i++) {
        if (sentence[i] == '(' || sentence[i] == '{' || sentence[i] == '[' || sentence[i] == ')' || sentence[i] == '}' || sentence[i] == ']')
            cnt += 1;
    }

    result = isBalanced(sentence, stack);

    if (result == 1)
        printf("OK_%d", cnt);
    else
        printf("Wrong_%d", cnt);


    return 0;
}
