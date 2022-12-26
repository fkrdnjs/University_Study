#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tree {           //tree 구조체
    int data;
    struct tree* left;
    struct tree* right;
}tree;

void newtree(tree* root, int elem, int left, int right) {   //새로운 트리 넣는 과정

    tree* lefttree = NULL, * righttree = NULL;      //왼쪽, 오른쪽 트리 NULL로 초기화

    if (root == NULL)                                   //root가 없으면 리턴
        return;

    if (root->data == elem) {                           //root elem 값과 일치할 경우
        if (left != 0) {                                //왼쪽 트리가 있을 경우 할당
            lefttree = (tree*)malloc(sizeof(tree));
            if (lefttree == NULL)
                return -1;

            lefttree->data = left;
            lefttree->left = NULL;
            lefttree->right = NULL;
        }

        if (right != 0) {                               //오른쪽 트리가 있을 경우 할당
            righttree = (tree*)malloc(sizeof(tree));
            if (righttree == NULL)
                return -1;

            righttree->data = right;
            righttree->left = NULL;
            righttree->right = NULL;
        }

        root->left = lefttree;                          //root에 연결
        root->right = righttree;

        return;
    }
    else {                                              //root elem과 일치하지 않으면 순회
        newtree(root->left, elem, left, right);
        newtree(root->right, elem, left, right);
    }
}

void printhelp(tree* root, char* command) {
    int i, len;

    len = strlen(command);

    printf(" %d", root->data);          //가장 위 루트 출력

    for (i = 0; i < len; i++) {         //문자열에 따라 이동하며 출력
        if (command[i] == 'L')
            root = root->left;
        else
            root = root->right;

        printf(" %d", root->data);
    }

    printf("\n");
}

void freehelp(tree* root) {         //재귀로 순회하며 프리하는 함수

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

    root = (tree*)malloc(sizeof(tree));         //가장 위 루트 할당
    if (root == NULL)
        return -1;

    root->data = elem;

    newtree(root, elem, left, right);            //루트에 연결

    for (i = 1; i < n; i++) {                    //연결 반복
        scanf("%d %d %d", &elem, &left, &right);
        newtree(root, elem, left, right);
    }

    scanf("%d", &scan);
    getchar();

    for (i = 0; i < scan; i++) {            //문자열 입력하고 함수 호출
        scanf("%s", command);
        printhelp(root, command);
    }

    freehelp(root);

    return 0;
}