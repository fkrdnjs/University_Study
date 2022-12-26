#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#pragma warning(disable:4996)

typedef struct tree {
    struct tree* lChild;
    struct tree* rChild;
    struct tree* parent;
    int key;
}tree;

tree* getnode();
tree* expandExternal(tree* w);
int isExternal(tree* w);
int isInternal(tree* w);
tree* sibling(tree* w);
tree* inOrderSucc(tree* w);
tree* reduceExternal(tree* z);
int findElement(tree* t, int k);
void insertItem(tree* t, int k);
tree* treeSearch(tree* t, int k);
int removeElement(tree* w, int k);
int isRoot(tree* w);
void printhelp(tree* t);
void freehelp(tree* t);

tree* root;

int main() {

    char command;
    int key, el;

    root = getnode();

    while (1) {

        scanf("%c", &command);
        getchar();

        if (command == 'i') {
            scanf("%d", &key);
            getchar();

            insertItem(root, key);
        }
        else if (command == 'd') {
            scanf("%d", &key);
            getchar();

            el = removeElement(root, key);

            if (el == -1)
                printf("X\n");
            else
                printf("%d\n", el);
        }
        else if (command == 's') {
            scanf("%d", &key);
            getchar();

            el = findElement(root, key);

            if (el == -1)
                printf("X\n");
            else
                printf("%d\n", el);
        }
        else if (command == 'p') {
            printhelp(root);
            printf("\n");
        }
        else if (command == 'q') {
            freehelp(root);
            break;
        }
    }

    return 0;
}

tree* getnode() {                       //���ο� Ʈ�� �����ϴ� �Լ�

    tree* new;

    new = (tree*)malloc(sizeof(tree));  //�����Ҵ� �ް�
    if (new == NULL)
        return -1;

    new->parent = NULL;                 //�ʱ�ȭ
    new->lChild = NULL;
    new->rChild = NULL;

    return new;
}

tree* expandExternal(tree* w) {         //�ܺγ��� Ȯ���ϴ� �Լ�

    tree* left, * right;

    left = getnode();                   //����, ������ �ڽ� ���� �� ����
    right = getnode();

    w->lChild = left;
    w->rChild = right;

    left->parent = w;
    right->parent = w;

    return w;
}

int isExternal(tree* w) {                       //�ܺ� ��� �Ǻ� �Լ�
    if (w->lChild == NULL && w->rChild == NULL)
        return 1;
    else
        return 0;
}

int isInternal(tree* w) {                       //���γ�� �Ǻ� �Լ�
    if (w->lChild != NULL && w->rChild != NULL)
        return 1;
    else
        return 0;
}

tree* sibling(tree* w) {                    //���� ��� ��ȯ �Լ�
    if (isRoot(w)) {                        //��Ʈ�� ��� ������ �����Ƿ� -1 ��ȯ
        return -1;
    }

    if (w->parent->lChild == w)             //�ݴ��� �ڽ� ��ȯ
        return w->parent->rChild;
    else
        return w->parent->lChild;
}

tree* inOrderSucc(tree* w) {                //������ȸ ����� ã�� �Լ�

    w = w->rChild;                          //���������� �ѹ� �̵�

    if (isExternal(w))                      //�ܺγ��� -1 ��ȯ
        return -1;
    else {
        while (isInternal(w->lChild))       //���γ���� ���� ��� ���� �ڽ����� �̵�
            w = w->lChild;
    }
    return w;                               //���� ������ ��� ��ȯ
}

tree* reduceExternal(tree* z) {             //Ʈ�� ��� ���� ���� �Լ�

    tree* w, * g;
    tree* zs;

    w = z->parent;              //w�� z�� �θ� ���
    zs = sibling(z);            //zs�� z�� ���� ���

    if (isRoot(w)) {            //w�� ��Ʈ�� ���
        root = zs;                 //��Ʈ�� zs�� �ϰ� parent �Ӽ� �ʱ�ȭ
        zs->parent = NULL;
    }
    else {
        g = w->parent;          //zs�� w�� �θ� ���� ����
        zs->parent = g;

        if (w == g->lChild)
            g->lChild = zs;
        else
            g->rChild = zs;
    }

    free(z);
    free(w);

    return zs;
}

int findElement(tree* t, int k) {   //k�� ���� ��� ������ key �� ��ȯ

    tree* w;

    w = treeSearch(t, k);           //Ʈ�� Ž��

    if (isExternal(w)) {
        return -1;
    }
    else
        return w->key;

}

void insertItem(tree* t, int k) {   //���� �Լ�

    tree* w;

    w = treeSearch(t, k);           //Ʈ�� Ž��

    if (isInternal(w))              //���� ��忡 ������ ��� -1 ��ȯ
        return -1;
    else {                          //���� ��� �� �����ϰ� �ܺγ��� Ȯ��
        w->key = k;
        w = expandExternal(w);
    }
}

tree* treeSearch(tree* t, int k) {      //Ʈ�� Ž�� �Լ�

    if (isExternal(t))
        return t;

    if (k == t->key)
        return t;
    else if (k < t->key)
        return treeSearch(t->lChild, k);
    else
        return treeSearch(t->rChild, k);
}

int removeElement(tree* t, int k) { //���ִ� �Լ�

    tree* w, * z, * y;
    int e;

    w = treeSearch(t, k);           //Ʈ�� Ž��

    if (isExternal(w))              //�ش��ϴ� �� ���� ��� -1 ��ȯ
        return -1;
    //�ش��ϴ� �� ���� ���
    e = w->key;
    z = w->lChild;

    if (isInternal(z))
        z = w->rChild;

    if (isExternal(z))              //�ܺγ���� ��� 
        reduceExternal(z);
    else {                          //���γ���� ���
        y = inOrderSucc(w);
        z = y->lChild;
        w->key = y->key;
        reduceExternal(z);
    }

    return e;                       //������ key ��ȯ
}

int isRoot(tree* w) {               //��Ʈ������� �Ǻ��ϴ� �Լ�
    if (w->parent == NULL)
        return 1;
    else
        return 0;
}

void printhelp(tree* t) {           //������ȸ ���

    if (isExternal(t))
        return;

    printf(" %d", t->key);

    printhelp(t->lChild);
    printhelp(t->rChild);

}

void freehelp(tree* t) {        //free�Լ�

    if (isExternal(t))
        return;

    freehelp(t->lChild);
    freehelp(t->rChild);

    free(t);

}