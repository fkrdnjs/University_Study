#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct NODE {                           //��� ����ü ����

    int elem;
    char name;
    struct NODE* enext;                         //��ҳؽ�Ʈ : ���η� �̵��ϴ� �ؽ�Ʈ
    struct NODE* gnext;                         //�׷�ؽ�Ʈ : ���Ϸ� �̵��ϴ� �ؽ�Ʈ

}node;

typedef struct groups {                         //�׷� ����ü ����
    node* header;
}g;

typedef struct elements {                       //���� ����ü ����
    node* header;
}e;

g group[5];                                     //���������� �׷� �迭, ���� �迭, ���� ����
e element[4];

int ne = 4;
int ng = 5;

void initShare() {                              //�ʱ�ȭ �Լ�

    int i;
    node* h;

    for (i = 0; i < ne; i++) {                  //���� �迭�� ��� �ʱ�ȭ
        h = (node*)malloc(sizeof(node));        //���ο� ��� ����
        if (h == NULL)
            return -1;

        h->gnext = h;                           //���ο� ����� �׷�ؽ�Ʈ�� �ڽ��� ����Ű���� �ʱ�ȭ
        element[i].header = h;                  //���� �迭�� ����� ���ο� ��� ����
    }

    for (i = 0; i < ng; i++) {                  //�׷� �迭�� ��� �ʱ�ȭ
        h = (node*)malloc(sizeof(node));
        if (h == NULL)
            return -1;

        h->enext = h;
        group[i].header = h;                    //�׷� �迭�� ����� ���ο� ��� ����
    }

}

void addShare(int el, char na) {                //�׷�, ������ �°� �߰��ϴ� �Լ�

    node* new;
    node* hg, * he;
    node* p;

    hg = group[na - 'A'].header;                //hg�� �׷�迭�� ����� �ʱ�ȭ
    p = hg->enext;                              //p�� ����� ��ҳؽ�Ʈ�� �ʱ�ȭ

    while (1) {

        if (p == hg)                            //p�� �ٽ� ����� ���ƿ� ��� ����
            break;

        else if (p->elem == el) {               //�ߺ��Ǵ� ��찡 ���� ��
            printf("Duplicate\n");              //duplicate ����ϰ� �Լ� �����Ŵ
            return -1;
        }

        p = p->enext;
    }
    // �ߺ��Ǵ� ��� ���� �� �߰���Ŵ
    new = (node*)malloc(sizeof(node));          //���ο� ��� ����
    if (new == NULL)
        return -1;

    hg = group[na - 'A'].header;                //hg�� �ش� �׷� �迭�� ����� �ʱ�ȭ
    new->enext = hg->enext;                     //���ο� ���� ������ ��� ������ �ִ� ���
    hg->enext = new;

    he = element[el - 1].header;                //he�� �ش� ���� �迭�� ����� �ʱ�ȭ
    new->gnext = he->gnext;                     //���������� ��� ������ ����
    he->gnext = new;

    new->elem = el;                             //��忡 �̸�, ������ �־���
    new->name = na;

    printf("OK\n");

}

void removeShare(int el, char na) {             //�����ϴ� �Լ�

    node* p;
    node* hg, * he;
    node* k;

    hg = group[na - 'A'].header;
    k = hg->enext;

    while (1) {

        if (k == hg) {                          //������ ��尡 ���� ��� �Լ� ����
            printf("NO Match\n");
            return -1;
        }

        if (k->elem == el)                      //������ ��� ������ ��� ����
            break;

        k = k->enext;
    }

    hg = group[na - 'A'].header;                //hg�� �׷� �迭�� ����� �ʱ�ȭ

    while (1) {
        if (hg->enext->elem == el) {            //prev�� ���� ������ hg �ؽ�Ʈ�� ������ ������ �����Ŵ
            p = hg->enext;                      //p���� ������ ��� ����
            break;
        }
        hg = hg->enext;
    }

    hg->enext = p->enext;                       //hg�� ��ҳؽ�Ʈ�� ������ ����� �ؽ�Ʈ ����Ű���� ��

    he = element[el - 1].header;                //���� �迭������ ���� ��������

    while (1) {
        if (he->gnext->name == na) {            //��ġ ã��
            p = he->gnext;
            break;
        }
        he = he->gnext;
    }

    he->gnext = p->gnext;                       //he�� ���� �ؽ�Ʈ�� ������ ����� �ؽ�Ʈ

    printf("OK\n");

    free(p);                                    //������ ��� ��������

}

void traverseShareElements(char k) {            //����� ���� ����� �Լ�

    node* h;
    node* p;

    h = group[k - 'A'].header;                  //�ش� ����� ����� �ʱ�ȭ
    p = h->enext;                               //p�� h�� ��ҳؽ�Ʈ�� �ʱ�ȭ

    if (p == h) {                               //����� ��Ұ� �ϳ��� ������ 0��� �� ����
        printf("0\n");
        return -1;
    }

    while (p != h) {                            //�ٽ� ����� �� ������ ���� ���
        printf("%d ", p->elem);
        p = p->enext;
    }

    printf("\n");
}

void traverseShareGroups(int k) {               //��� ����� �Լ�

    node* h;
    node* p;

    h = element[k - 1].header;                  //�ش� ������ ����� �ʱ�ȭ
    p = h->gnext;

    if (p == h) {                               //���� ���� ��� ������ 0��� �� ����
        printf("0\n");
        return -1;
    }

    while (p != h) {                            //�ٽ� ����� �� ������ �̸� ���
        printf("%c ", p->name);
        p = p->gnext;
    }

    printf("\n");
}

void pexit() {                                  //�������ִ� �Լ�

    node* he, * p, * hg, * del;
    int i;

    for (i = 0; i < ne; i++) {                  //���� �迭 �������ִ� �κ�
        he = element[i].header;                 //����� �ʱ�ȭ
        p = he->gnext;                          //����� �ؽ�Ʈ�� �ʱ�ȭ

        while (1) {

            if (p == he)                        //�ٽ� ����� ���ƿ��� �������� �ʰ� Ż��
                break;

            del = p;
            p = p->gnext;

            free(del);                          //�߰��� ���� ����

        }

        free(he);                               //���� �迭�� ��� ����
    }

    for (i = 0; i < ng; i++) {
        hg = group[i].header;                   //�׷� �迭�� ����� �ʱ�ȭ

        free(hg);                               //�׷� �迭�� ��� ����
    }

}

int main(void) {

    int i, e;
    char cmd, g;
    int flag = 0;

    initShare();                                //�ʱ�ȭ �ϴ� �Լ� ȣ��

    while (1) {

        scanf("%c", &cmd);                      //Ŀ�ǵ� �Է�
        getchar();

        switch (cmd) {
        case 'a':                           //a�� ���
            scanf("%d", &e);
            getchar();

            scanf("%c", &g);
            getchar();

            addShare(e, g);                 //addShare ȣ��
            break;

        case 'r':                           //r�� ���
            scanf("%d", &e);
            getchar();

            scanf("%c", &g);
            getchar();

            removeShare(e, g);              //removeShare ȣ��
            break;

        case 'e':                           //e�� ���
            scanf("%c", &g);
            getchar();

            traverseShareElements(g);       //traverseShareElements ȣ��
            break;

        case 'g':                           //g�� ���
            scanf("%d", &e);
            getchar();

            traverseShareGroups(e);         //traverseShareGroups ȣ��
            break;

        default:                            //�� ���� ���
            pexit();                        //���� ���� ��
            flag = 1;                       //�÷��� ���� 1�� ����� ��
            break;

        }

        if (flag == 1)                          //�÷��� ���� 1�̸� while�� Ż���ϰ� ����
            break;
    }

    return 0;
}