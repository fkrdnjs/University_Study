#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tree {           //tree ����ü
    int data;
    struct tree* left;
    struct tree* right;
}tree;

void newtree(tree* root, int elem, int left, int right) {   //���ο� Ʈ�� �ִ� ����

    tree* lefttree = NULL, * righttree = NULL;      //����, ������ Ʈ�� NULL�� �ʱ�ȭ

    if (root == NULL)                                   //root�� ������ ����
        return;

    if (root->data == elem) {                           //root elem ���� ��ġ�� ���
        if (left != 0) {                                //���� Ʈ���� ���� ��� �Ҵ�
            lefttree = (tree*)malloc(sizeof(tree));
            if (lefttree == NULL)
                return -1;

            lefttree->data = left;
            lefttree->left = NULL;
            lefttree->right = NULL;
        }

        if (right != 0) {                               //������ Ʈ���� ���� ��� �Ҵ�
            righttree = (tree*)malloc(sizeof(tree));
            if (righttree == NULL)
                return -1;

            righttree->data = right;
            righttree->left = NULL;
            righttree->right = NULL;
        }

        root->left = lefttree;                          //root�� ����
        root->right = righttree;

        return;
    }
    else {                                              //root elem�� ��ġ���� ������ ��ȸ
        newtree(root->left, elem, left, right);
        newtree(root->right, elem, left, right);
    }
}

void printhelp(tree* root, char* command) {
    int i, len;

    len = strlen(command);

    printf(" %d", root->data);          //���� �� ��Ʈ ���

    for (i = 0; i < len; i++) {         //���ڿ��� ���� �̵��ϸ� ���
        if (command[i] == 'L')
            root = root->left;
        else
            root = root->right;

        printf(" %d", root->data);
    }

    printf("\n");
}

void freehelp(tree* root) {         //��ͷ� ��ȸ�ϸ� �����ϴ� �Լ�

    if (root == NULL)
        return;

    freehelp(root->left);
    freehelp(root->right);
    free(root);
}

int main() {

    int n, i, scan;
    int elem, left, right;
    char command[101];
    tree* root;

    scanf("%d", &n);

    scanf("%d %d %d", &elem, &left, &right);

    root = (tree*)malloc(sizeof(tree));         //���� �� ��Ʈ �Ҵ�
    if (root == NULL)
        return -1;

    root->data = elem;

    newtree(root, elem, left, right);            //��Ʈ�� ����

    for (i = 1; i < n; i++) {                    //���� �ݺ�
        scanf("%d %d %d", &elem, &left, &right);
        newtree(root, elem, left, right);
    }

    scanf("%d", &scan);
    getchar();

    for (i = 0; i < scan; i++) {            //���ڿ� �Է��ϰ� �Լ� ȣ��
        scanf("%s", command);
        printhelp(root, command);
    }

    freehelp(root);

    return 0;
}