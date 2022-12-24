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

void preorder(tree* root) {

    if (root == NULL)
        return;

    printf(" %d", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(tree* root) {

    if (root == NULL)
        return;

    inorder(root->left);
    printf(" %d", root->data);
    inorder(root->right);
}

void postorder(tree* root) {

    if (root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    printf(" %d", root->data);
}

void find(tree* root, int order, int id) {

    if (root == NULL)
        return;

    if (root->id == id) {
        if (order == 1)
            preorder(root);

        else if (order == 2)
            inorder(root);

        else if (order == 3)
            postorder(root);
    }

    else {
        find(root->left, order, id);
        find(root->right, order, id);
    }
}

void freehelp(tree* root) {

    if (root == NULL)
        return -1;

    freehelp(root->left);
    freehelp(root->right);
    free(root);
}

int main(void) {

    int x, y;
    tree* left, * right, * root;
    tree* first_tree;

    scanf("%d %d", &x, &y);

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
        find(root, x, y);

    freehelp(root);

    return 0;
}
