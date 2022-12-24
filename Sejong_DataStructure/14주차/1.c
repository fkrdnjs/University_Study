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

void newtree(tree* root, int rvalue, int svalue1, int svalue2) {

    tree* lefttree = NULL;
    tree* righttree = NULL;

    if (root == NULL)
        return;

    if (root->data == rvalue) {

        if (svalue1 != 0) {
            lefttree = (tree*)malloc(sizeof(tree));
            if (lefttree == NULL)
                return -1;

            lefttree->data = svalue1;
            lefttree->left = NULL;
            lefttree->right = NULL;
        }

        if (svalue2 != NULL) {
            righttree = (tree*)malloc(sizeof(tree));
            if (righttree == NULL)
                return -1;

            righttree->data = svalue2;
            righttree->left = NULL;
            righttree->right = NULL;
        }

        root->left = lefttree;
        root->right = righttree;

        return;
    }

    else {
        newtree(root->left, rvalue, svalue1, svalue2);
        newtree(root->right, rvalue, svalue1, svalue2);
    }

}

void printhelp(tree* root, char* str) {

    char* p = str;

    if (root != NULL)
        printf(" %d", root->data);

    if (*p == '\0') {
        printf("\n");
        return;
    }
    else if (*p == 'R') {
        printhelp(root->right, p + 1);
    }
    else if (*p == 'L') {
        printhelp(root->left, p + 1);
    }

}

void freehelp(tree* root) {

    if (root == NULL)
        return;

    freehelp(root->left);
    freehelp(root->right);
    free(root);
}

int main(void) {

    int node, search;
    int i;
    char str[101] = { '\0' };
    int rv, sv1, sv2;
    tree* root;
    tree* first;

    scanf("%d", &node);
    scanf("%d %d %d", &rv, &sv1, &sv2);

    first = (tree*)malloc(sizeof(tree));
    if (first == NULL)
        return -1;

    root = first;
    first->data = rv;

    newtree(root, rv, sv1, sv2);

    for (i = 1; i < node; i++) {
        scanf("%d %d %d", &rv, &sv1, &sv2);
        newtree(root, rv, sv1, sv2);
    }

    scanf("%d", &search);
    getchar();

    for (i = 0; i < search; i++) {
        scanf("%s", str);
        printhelp(root, str);
    }

    freehelp(root);

    return 0;
}
