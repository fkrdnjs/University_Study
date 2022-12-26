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
    int height;
}tree;

tree* getnode();
void expandExternal(tree* w);
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

int updateHeight(tree* w);
int isBalanced(tree* w);
tree* restructure(tree* x, tree* y, tree* z);
void searchAndFixAfterInsertion(tree* w);
void searchAndFixAfterRemoval(tree* z);

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

void expandExternal(tree* w) {         //�ܺγ��� Ȯ���ϴ� �Լ�

    tree* left, * right;

    left = getnode();                   //����, ������ �ڽ� ���� �� ����
    right = getnode();

    left->height = 0;
    right->height = 0;
    left->parent = w;
    right->parent = w;

    w->lChild = left;
    w->rChild = right;
    w->height = 1;

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

    if (isExternal(w))
        return -1;
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
        expandExternal(w);
        searchAndFixAfterInsertion(w);
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

    tree* w, * z, * y, * zs;
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
        zs = reduceExternal(z);
    else {                          //���γ���� ���
        y = inOrderSucc(w);
        z = y->lChild;
        w->key = y->key;
        zs = reduceExternal(z);
    }

    searchAndFixAfterRemoval(zs->parent);

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

int updateHeight(tree* w) {     //��� ���� �����ϴ� �Լ�

    int h;

    if (w->lChild->height > w->rChild->height)
        h = w->lChild->height + 1;
    else
        h = w->rChild->height + 1;

    if (h != w->height) {
        w->height = h;
        return 1;
    }
    else
        return 0;

}

int isBalanced(tree* w) {       //���� ���θ� ��ȯ�ϴ� �Լ�

    int cha;

    cha = w->lChild->height - w->rChild->height;    //�ڽ� ������ ����

    if (2 > cha && cha > -2)    // ���밪���� -1 ~ 1 ���̰� ���� ����
        return 1;
    else
        return 0;
}

tree* restructure(tree* x, tree* y, tree* z) {  //��� ����

    tree* a, * b, * c;
    tree* t0, * t1, * t2, * t3;

    if (z->key < y->key && y->key < x->key) {
        a = z;
        b = y;
        c = x;

        t0 = a->lChild;
        t1 = b->lChild;
        t2 = c->lChild;
        t3 = c->rChild;
    }
    else if (x->key < y->key && y->key < z->key) {
        a = x;
        b = y;
        c = z;

        t0 = a->lChild;
        t1 = a->rChild;
        t2 = b->rChild;
        t3 = c->rChild;
    }
    else if (y->key < x->key && x->key < z->key) {
        a = y;
        b = x;
        c = z;

        t0 = a->lChild;
        t1 = b->lChild;
        t2 = b->rChild;
        t3 = c->rChild;
    }
    else {
        a = z;
        b = x;
        c = y;

        t0 = a->lChild;
        t1 = b->lChild;
        t2 = b->rChild;
        t3 = c->rChild;
    }

    if (isRoot(z)) {
        root = b;
        b->parent = NULL;
    }
    else if (z->parent->lChild == z) {
        z->parent->lChild = b;
        b->parent = z->parent;
    }
    else {
        z->parent->rChild = b;
        b->parent = z->parent;
    }

    a->lChild = t0;
    a->rChild = t1;
    t0->parent = a;
    t1->parent = a;
    updateHeight(a);

    c->lChild = t2;
    c->rChild = t3;
    t2->parent = c;
    t3->parent = c;
    updateHeight(c);

    b->lChild = a;
    b->rChild = c;
    a->parent = b;
    c->parent = b;
    updateHeight(b);

    return b;
}

void searchAndFixAfterInsertion(tree* w) {  //���� �˻� ���� �� �ұ��� ������ ����

    tree* x, * y, * z;

    w->lChild->height = 0;
    w->rChild->height = 0;
    w->height = 1;

    if (isRoot(w))
        return;

    z = w->parent;

    while (updateHeight(z) && isBalanced(z)) {
        if (isRoot(z))
            return;
        z = z->parent;
    }

    if (isBalanced(z))
        return;

    if (z->lChild->height > z->rChild->height)
        y = z->lChild;
    else
        y = z->rChild;

    if (y->lChild->height > y->rChild->height)
        x = y->lChild;
    else
        x = y->rChild;

    restructure(x, y, z);

    return;
}

void searchAndFixAfterRemoval(tree* z) {        //

    tree* x, * y, * b;

    while (updateHeight(z) && isBalanced(z)) {
        if (isRoot(z))
            return;
        z = z->parent;
    }

    if (isBalanced(z))
        return;

    if (z->lChild->height > z->rChild->height)
        y = z->lChild;
    else
        y = z->rChild;

    if (y->lChild->height > y->rChild->height)
        x = y->lChild;
    else if (y->lChild->height < y->rChild->height)
        x = y->rChild;
    else {
        if (z->lChild == y)
            x = y->lChild;
        else
            x = y->rChild;
    }

    b = restructure(x, y, z);

    if (isRoot(b))
        return;

    searchAndFixAfterRemoval(b->parent);

}