#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct tree {
    int data;
    struct tree* left;
    struct tree* right;
}tree;

tree* newdown(int el) {

    tree* new;

    new = (tree*)malloc(sizeof(tree));
    if (new == NULL)
        return -1;

    new->data = el;
    new->left = 0;
    new->right = 0;

    return new;
}

tree* newup(tree* lefttree, tree* righttree, int el) {

    tree* new;

    new = (tree*)malloc(sizeof(tree));
    if (new == NULL)
        return -1;

    new->data = el;
    new->left = lefttree;
    new->right = righttree;

    return new;

}

int main(void)
{
    int n, i;
    tree* F[8];

    scanf("%d", &n);

    F[6] = newdown(130);
    F[7] = newdown(80);
    F[3] = newdown(70);
    F[4] = newdown(90);

    F[5] = newup(F[6], F[7], 120);
    F[1] = newup(F[3], F[4], 30);
    F[2] = newup(0, F[5], 50);
    F[0] = newup(F[1], F[2], 20);

    if (1 <= n && n <= 8) {
        printf("%d ", F[n - 1]->data);

        if (F[n - 1]->left != 0)
            printf("%d ", F[n - 1]->left->data);

        if (F[n - 1]->right != 0)
            printf("%d", F[n - 1]->right->data);
    }
    else
        printf("-1");

    for (i = 0; i < 8; i++)
        free(F[i]);

    return 0;
}
