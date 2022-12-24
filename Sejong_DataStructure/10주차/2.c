#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int top = -1;

void push(char* stack, char k) {

    top += 1;
    stack[top] = k;

}

char pop(char* stack) {

    top -= 1;
    return stack[top + 1];

}

int isoperand(char k) {
    if (k >= '0' && k <= '9')
        return 1;
    else
        return 0;
}

int main(void)
{
    char formula[101];
    char stack[101] = { '\0' };
    int i, j, len;
    int n, result;
    char a, b;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {

        scanf("%s", formula);
        len = strlen(formula);

        for (j = 0; j < len; j++) {

            if (isoperand(formula[j]) == 1)
                push(stack, formula[j]);

            else {
                if (formula[j] == '+') {
                    a = pop(stack) - '0';
                    b = pop(stack) - '0';
                    push(stack, a + b + '0');
                }
                else if (formula[j] == '-') {
                    a = pop(stack) - '0';
                    b = pop(stack) - '0';
                    push(stack, b - a + '0');
                }
                else if (formula[j] == '*') {
                    a = pop(stack) - '0';
                    b = pop(stack) - '0';
                    push(stack, a * b + '0');
                }
                else if (formula[j] == '/') {
                    a = pop(stack) - '0';
                    b = pop(stack) - '0';
                    push(stack, b / a + '0');
                }
            }
        }
        printf("%d\n", pop(stack) - '0');
    }


    return 0;
}
