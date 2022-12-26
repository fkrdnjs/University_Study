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

/* 명령어

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

/*명령어 수행 결과

i 33 -> 8번 자리에 33 들어감
f 24 -> NoSuchKey 출력
r 25 -> 2번 자리에 있는 25 제거
f 25 -> NoSuchKey
i 25 -> 2번 자리에 25 들어감
r 4 -> NoSuchKey
f 5 -> 5 출력
i 44 -> 13번 자리에 44 들어감
r 50 -> 4번 자리에 있는 50 제거
q -> 종료

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

            if (cnt != 23) {    //23개 이하로 입력된 경우
                if (findElement(k, q) != -1) {  //겹치는 원소가 있을 경우
                    printf("Duplicated Exception\n");
                }
                else {  //겹치는 원소 없으면
                    insertItem(k, q);
                }
            }
            else                //23개 초과 입력된 경우
                printf("Full Table Exception\n");

            showHashTable();
        }
        else if (command == 'f') {
            scanf("%d", &k);
            getchar();

            res = findElement(k, q);

            if (res == -1)  //입력된 원소가 없으면
                printf("NoSuchKey\n");
            else            //원소 출력
                printf("%d\n", res);

        }
        else if (command == 'r') {
            scanf("%d", &k);
            getchar();

            res = removeElement(k, q);

            if (res == -1)      //입력된 원소 없으면
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
        new[i].data = -1;   //초기 데이터 -1로 초기화
        new[i].flag = 0;
    }

    return new;
}

void initTable(int q) {

    int i;
    int k = 0;

    for (i = 0; i < 20; i++) {  //0부터 95까지 테이블에 넣기
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

초기 버켓은 비어있는걸로 시작

항목 삽입되면 활성 버켓
항목 삭제되면 비활성 버켓

탐색 중 비활성 버켓은 사용중인 버켓으로 취급
삽입 중 비활성 버켓은 비어 있는 버켓으로 취급하여 이곳에 삽입

*/