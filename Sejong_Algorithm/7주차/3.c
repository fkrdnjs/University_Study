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

tree* getnode() {                       //새로운 트리 생성하는 함수

    tree* new;

    new = (tree*)malloc(sizeof(tree));  //동적할당 받고
    if (new == NULL)
        return -1;

    new->parent = NULL;                 //초기화
    new->lChild = NULL;
    new->rChild = NULL;

    return new;
}

void expandExternal(tree* w) {         //외부노드로 확장하는 함수

    tree* left, * right;

    left = getnode();                   //왼쪽, 오른쪽 자식 생성 후 연결
    right = getnode();

    left->height = 0;
    right->height = 0;
    left->parent = w;
    right->parent = w;

    w->lChild = left;
    w->rChild = right;
    w->height = 1;

}

int isExternal(tree* w) {                       //외부 노드 판별 함수
    if (w->lChild == NULL && w->rChild == NULL)
        return 1;
    else
        return 0;
}

int isInternal(tree* w) {                       //내부노드 판별 함수
    if (w->lChild != NULL && w->rChild != NULL)
        return 1;
    else
        return 0;
}

tree* sibling(tree* w) {                    //형제 노드 반환 함수
    if (isRoot(w)) {                        //루트일 경우 형제가 없으므로 -1 반환
        return -1;
    }

    if (w->parent->lChild == w)             //반대쪽 자식 반환
        return w->parent->rChild;
    else
        return w->parent->lChild;
}

tree* inOrderSucc(tree* w) {                //중위순회 계승자 찾는 함수

    w = w->rChild;                          //오른쪽으로 한번 이동

    if (isExternal(w))                      //외부노드면 -1 반환
        return -1;
    else {
        while (isInternal(w->lChild))       //내부노드인 동안 계속 왼쪽 자식으로 이동
            w = w->lChild;
    }
    return w;                               //가장 마지막 노드 반환
}

tree* reduceExternal(tree* z) {             //트리 노드 삭제 위한 함수

    tree* w, * g;
    tree* zs;

    w = z->parent;              //w는 z의 부모 노드
    zs = sibling(z);            //zs는 z의 형제 노드

    if (isRoot(w)) {            //w가 루트일 경우
        root = zs;                 //루트를 zs로 하고 parent 속성 초기화
        zs->parent = NULL;
    }
    else {
        g = w->parent;          //zs를 w의 부모 노드로 연결
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

int findElement(tree* t, int k) {   //k를 가진 노드 있으면 key 값 반환

    tree* w;

    w = treeSearch(t, k);           //트리 탐색

    if (isExternal(w))
        return -1;
    else
        return w->key;
}

void insertItem(tree* t, int k) {   //삽입 함수

    tree* w;

    w = treeSearch(t, k);           //트리 탐색

    if (isInternal(w))              //내부 노드에 존재할 경우 -1 반환
        return -1;
    else {                          //없을 경우 값 대입하고 외부노드로 확장
        w->key = k;
        expandExternal(w);
        searchAndFixAfterInsertion(w);
    }
}

tree* treeSearch(tree* t, int k) {      //트리 탐색 함수

    if (isExternal(t))
        return t;

    if (k == t->key)
        return t;
    else if (k < t->key)
        return treeSearch(t->lChild, k);
    else
        return treeSearch(t->rChild, k);
}

int removeElement(tree* t, int k) { //없애는 함수

    tree* w, * z, * y, * zs;
    int e;

    w = treeSearch(t, k);           //트리 탐색

    if (isExternal(w))              //해당하는 값 없을 경우 -1 반환
        return -1;
    //해당하는 값 있을 경우
    e = w->key;
    z = w->lChild;

    if (isInternal(z))
        z = w->rChild;

    if (isExternal(z))              //외부노드일 경우 
        zs = reduceExternal(z);
    else {                          //내부노드일 경우
        y = inOrderSucc(w);
        z = y->lChild;
        w->key = y->key;
        zs = reduceExternal(z);
    }

    searchAndFixAfterRemoval(zs->parent);

    return e;                       //삭제된 key 반환
}

int isRoot(tree* w) {               //루트노드인지 판별하는 함수
    if (w->parent == NULL)
        return 1;
    else
        return 0;
}

void printhelp(tree* t) {           //전위순회 출력

    if (isExternal(t))
        return;

    printf(" %d", t->key);

    printhelp(t->lChild);
    printhelp(t->rChild);

}

void freehelp(tree* t) {        //free함수

    if (isExternal(t))
        return;

    freehelp(t->lChild);
    freehelp(t->rChild);

    free(t);

}

int updateHeight(tree* w) {     //노드 높이 갱신하는 함수

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

int isBalanced(tree* w) {       //균형 여부를 반환하는 함수

    int cha;

    cha = w->lChild->height - w->rChild->height;    //자식 높이의 차이

    if (2 > cha && cha > -2)    // 절대값으로 -1 ~ 1 차이가 나면 정상
        return 1;
    else
        return 0;
}

tree* restructure(tree* x, tree* y, tree* z) {  //노드 개조

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

void searchAndFixAfterInsertion(tree* w) {  //균형 검사 수행 후 불균형 있으면 개조

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