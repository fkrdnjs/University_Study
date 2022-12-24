#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int count = 0;                                          //ù ��° Ʈ�������� �Ǻ��ϴ� ��������

typedef struct tree {                                   //Ʈ�� ����ü
    char elem[101];                                     //������ ����, ���� �ڽ�, ������ �ڽ��� ���ҷ� ����.   
    struct tree* left;
    struct tree* right;
    struct tree* parent;                                //�θ� Ʈ���� �ּ� �����ϴ� ����
}tree;

tree* newtree() {                                       //���ο� Ʈ�� �����ϴ� �Լ�

    tree* new;

    new = (tree*)malloc(sizeof(tree));                  //���ο� Ʈ�� �����Ҵ�
    if (new == NULL)
        return -1;

    new->left = NULL;                                   //����, ������ �ڽ� NULL�� �ʱ�ȭ
    new->right = NULL;

    return new;
}

tree* makeExternalNode() {                              //�ܺ�Ʈ�� ����� �Լ�

    tree* v;

    v = newtree();                                     //���ο� Ʈ�� ����

    printf("Enter decision:");

    gets(v->elem);                                      //��� ����

    return v;
}

tree* makeInternalNode(int k) {                         //���� Ʈ�� �����ϴ� �Լ�

    tree* v;
    char answer[4];

    v = newtree();                                      //���ο� Ʈ�� ����

    if (count == 0) {                                   //ù ��° Ʈ���� ��� �θ� ���Ҹ� NULL�� �ʱ�ȭ
        v->parent = NULL;
        count += 1;                                     //���� count ������ ������� ����
    }

    printf("Enter question : ");
    gets(v->elem);                                      //���� �Է�

    printf("Question if yes to '%s'? ", v->elem);
    scanf("%s", answer);                                //��� �Է�
    getchar();

    if (k == 0 || k == 1) {                             //ù��° Ȥ�� �� ��° ������ ���
        if (strcmp(answer, "yes") == 0)                 //��信 ������� ������ ���� ����
            v->left = makeInternalNode(k + 1);
        else if ((strcmp(answer, "no") == 0))
            v->left = makeInternalNode(k + 1);
        v->left->parent = v;                            //left�� �θ� ��Ҹ� v��

        printf("Question if no to '%s'? ", v->elem);
        scanf("%s", answer);
        getchar();

        if (strcmp(answer, "yes") == 0)                 //������ ���� �����
            v->right = makeInternalNode(k + 1);
        else if ((strcmp(answer, "no") == 0))
            v->right = makeInternalNode(k + 1);
        v->right->parent = v;                           //right�� �θ� ��Ҹ� v��
    }

    else if (k == 2 || k == 3) {                        //����° Ȥ�� �׹�° ������ ���
        if (strcmp(answer, "yes") == 0)                 //yes�� ��� ���� �����
            v->left = makeInternalNode(k + 1);
        else if ((strcmp(answer, "no") == 0))           //no�� ��� ��� �����
            v->left = makeExternalNode();
        v->left->parent = v;

        printf("Question if no to '%s'? ", v->elem);
        scanf("%s", answer);
        getchar();

        if (strcmp(answer, "yes") == 0)                 //�ݺ�
            v->right = makeInternalNode(k + 1);
        else if ((strcmp(answer, "no") == 0))
            v->right = makeExternalNode();
        v->right->parent = v;
    }

    else {                                              //�ټ���° ���� �̻��� ���
        if (strcmp(answer, "yes") == 0)                 //answer�� ��� ���� ������ �亯 �����
            v->left = makeExternalNode();
        else if ((strcmp(answer, "no") == 0))
            v->left = makeExternalNode();
        v->left->parent = v;

        printf("Question if no to '%s'? ", v->elem);
        scanf("%s", answer);
        getchar();

        if (strcmp(answer, "yes") == 0)                 //�ݺ�
            v->right = makeExternalNode();
        else if ((strcmp(answer, "no") == 0))
            v->right = makeExternalNode();
        v->right->parent = v;
    }

}

tree* buildDecisionTree() {                             //���� �����ϴ� �Լ�

    return makeInternalNode(0);                         //���� ó������ 0�� ���ڷ� �ְ� ��ͷ� ���鼭 1�� �����ϴ� ���

}

void processNode(tree* root) {                          //���� Ȥ�� �亯 ����ϴ� �Լ�

    char answer[4];

    printf("%s ", root->elem);                          //���

    if (root->left == NULL && root->right == NULL) {    //������ Ʈ���� ��� �ٹٲٰ� ����
        printf("\n");
        return;
    }

    scanf("%s", answer);                                //�亯 �Է�
    getchar();

    if (strcmp(answer, "yes") == 0)                     //yes�� ��� �������� �̵�
        processNode(root->left);
    else if (strcmp(answer, "no") == 0)                 //no�� ��� ���������� �̵�
        processNode(root->right);
}

void runDecisionTree(tree* root) {                                               //������� ��� �Է¹޴� �Լ�

    printf("***Please answer questions\n");
    processNode(root);
}

void freehelp(tree* root) {                                                     //��ü Ʈ�� ���� �����ִ� �Լ�

    if (root == NULL)                                                           //������ Ʈ���� ����
        return;

    freehelp(root->left);                                                       //��ͷ� ���鼭 ��� �̵�
    freehelp(root->right);
    free(root);
}

int main(void) {

    tree* root;
    int i;

    root = buildDecisionTree();                                  //buildDecisionTree �Լ� ȣ��
    printf("Tree complete. Now Running!!\n");

    while (1) {
        if (root->parent == NULL)                               //root�� ���� ���� ����Ű���� �ϴ� �ڵ�
            break;
        root = root->parent;
    }

    for (i = 0; i < 3; i++) {                                    //���� runDecisionTree �Լ� ȣ��
        runDecisionTree(root);
    }

    freehelp(root);                                              //�Ҵ�� Ʈ�� ���� �� ����

    return 0;
}