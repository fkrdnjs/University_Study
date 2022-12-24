#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct tree {
    int data;
    int id;
    struct tree* left;
    struct tree* right;
}tree;

tree* newtree(int id, int data) {

    tree* new;

    new = (tree*)malloc(sizeof(tree));
    if (new == NULL)
        return -1;

    new->id = id;
    new->data = data;
    new->left = 0;
    new->right = 0;

    return new;

}

void direction(tree* parent, tree* lefttree, tree* righttree) {

    parent->left = lefttree;
    parent->right = righttree;

}

int preorder(tree* root, int k) {

    int sum = k;

    if (root == NULL)
        return;

    sum += root->data;

    sum = preorder(root->left, sum);
    sum = preorder(root->right, sum);

    return sum;
}


void find(tree* root, int y) {

    int result = 0;

    if (root == NULL)
        return;

    if (root->id == y) {
        result = preorder(root, 0);
        printf("%d", result);
    }
    else {
        find(root->left, y);
        find(root->right, y);
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

    int y;
    tree* left, * right, * root;
    tree* first_tree;

    scanf("%d", &y);

    root = newtree(1, 20);

    first_tree = root;

    left = newtree(2, 30);
    right = newtree(3, 50);
    direction(root, left, right);

    left = newtree(4, 70);
    right = newtree(5, 90);
    direction(root->left, left, right);

    left = 0;
    right = newtree(6, 120);
    direction(root->right, left, right);

    left = newtree(7, 130);
    right = newtree(8, 80);
    direction(root->right->right, left, right);

    if (y <= 0 || y > 8)
        printf("-1");
    else
        find(root, y);

    freehelp(root);

    return 0;
}
