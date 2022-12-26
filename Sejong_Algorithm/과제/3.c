#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)

typedef struct table {
    int data;
    int flag;
}table;

table* x;
int M = 23;
int cnt = 0;

int h(int k);
int h2(int k, int q);
table* createHashTable();
void initTable(int q);
int getNextBucket(int k, int i, int q);
void insertItem(int k, int q);
int findElement(int k, int q);
int removeElement(int k, int q);
void showHashTable();

/* ��ɾ�

i 33
f 24
r 25
f 25
i 25
r 4
f 5
i 44
r 50
q

*/

/*��ɾ� ���� ���

i 33 -> 8�� �ڸ��� 33 ��
f 24 -> NoSuchKey ���
r 25 -> 2�� �ڸ��� �ִ� 25 ����
f 25 -> NoSuchKey
i 25 -> 2�� �ڸ��� 25 ��
r 4 -> NoSuchKey
f 5 -> 5 ���
i 44 -> 13�� �ڸ��� 44 ��
r 50 -> 4�� �ڸ��� �ִ� 50 ����
q -> ����

*/

int main() {

    char command;
    int q;
    int i, k;
    int res, random;

    q = 19;
    x = createHashTable();
    initTable(q);

    while (1) {
        scanf("%c", &command);

        if (command == 'i') {
            scanf("%d", &k);
            getchar();

            if (cnt != 23) {    //23�� ���Ϸ� �Էµ� ���
                if (findElement(k, q) != -1) {  //��ġ�� ���Ұ� ���� ���
                    printf("Duplicated Exception\n");
                }
                else {  //��ġ�� ���� ������
                    insertItem(k, q);
                }
            }
            else                //23�� �ʰ� �Էµ� ���
                printf("Full Table Exception\n");

            showHashTable();
        }
        else if (command == 'f') {
            scanf("%d", &k);
            getchar();

            res = findElement(k, q);

            if (res == -1)  //�Էµ� ���Ұ� ������
                printf("NoSuchKey\n");
            else            //���� ���
                printf("%d\n", res);

        }
        else if (command == 'r') {
            scanf("%d", &k);
            getchar();

            res = removeElement(k, q);

            if (res == -1)      //�Էµ� ���� ������
                printf("NoSuchKey\n");

            showHashTable();
        }

        else if (command == 'q') {
            free(x);
            break;
        }
    }

    return 0;
}

int h(int k) {
    return k % M;
}

int h2(int k, int q) {
    return q - (k % q);
}

table* createHashTable() {

    int i;
    table* new;

    new = (table*)malloc(sizeof(table) * M);
    if (new == NULL)
        return -1;

    for (i = 0; i < M; i++) {
        new[i].data = -1;   //�ʱ� ������ -1�� �ʱ�ȭ
        new[i].flag = 0;
    }

    return new;
}

void initTable(int q) {

    int i;
    int k = 0;

    for (i = 0; i < 20; i++) {  //0���� 95���� ���̺� �ֱ�
        insertItem(k, q);
        k += 5;
    }

}

int getNextBucket(int i, int k, int q) {
    return (h(k) + i * h2(k, q)) % M;
}

void insertItem(int k, int q) {

    int index;
    int i;

    for (i = 0; i < M; i++) {

        index = getNextBucket(i, k, q);

        if (x[index].data == -1 || x[index].flag == 0) {

            x[index].data = k;
            x[index].flag = 1;
            cnt += 1;

            return;
        }
    }
}

int findElement(int k, int q) {

    int index;
    int i;

    for (i = 0; i < M; i++) {

        index = getNextBucket(i, k, q);

        if (x[index].data == k && x[index].flag == 1)
            return x[index].data;

    }

    return -1;
}

int removeElement(int k, int q) {

    int index;
    int i, res;

    for (i = 0; i < M; i++) {

        index = getNextBucket(i, k, q);

        if (x[index].data == k && x[index].flag == 1) {
            res = x[index].data;
            x[index].data = -1;
            x[index].flag = 0;
            cnt -= 1;

            return res;
        }
    }

    return -1;
}

void showHashTable() {

    int i;

    for (i = 0; i < M; i++)
        printf("%3d", i);

    printf("\n");

    for (i = 0; i < M; i++) {
        if (x[i].data != -1)
            printf("%3d", x[i].data);
        else
            printf("  .");
    }

    printf("\n");
}

/*

�ʱ� ������ ����ִ°ɷ� ����

�׸� ���ԵǸ� Ȱ�� ����
�׸� �����Ǹ� ��Ȱ�� ����

Ž�� �� ��Ȱ�� ������ ������� �������� ���
���� �� ��Ȱ�� ������ ��� �ִ� �������� ����Ͽ� �̰��� ����

*/