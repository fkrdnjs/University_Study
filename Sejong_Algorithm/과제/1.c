#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#pragma warning(disable:4996)

int* buildList(int n, int min, int max);
void writeList(int* L, int n);
int findKthSmallest(int* L, int n, int k);
void buildHeap(int* L, int n);
void downHeap(int* L, int index, int n);
void swapElements(int* L, int index1, int index2);
int removeMin(int* L, int n);
int* copy(int* L, int n);

int main() {

    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start, end, diff;
    int* L, * H;
    int output[5] = { 0 }, karray[4] = { 1, 100, 99900, 99999 };
    int i, k, result;

    srand(time(NULL));
    QueryPerformanceFrequency(&ticksPerSec);

    L = buildList(10, 1, 100);                  //초기 리스트 생성
    H = copy(L, 10);                            //초기 리스트를 H에 복사
    writeList(L, 10);

    for (k = 1; k <= 3; k++) {
        L = copy(H, 10);                        //초기 리스트를 L에 복사
        output[k] = findKthSmallest(L, 10, k);  //output에 결과값 저장
    }

    writeList(output, 3);

    free(L);                            //할당받은 리스트들 프리
    free(H);

    L = buildList(100000, 1, 1000000);  //초기 리스트 생성
    H = copy(L, 100000);                //초기 리스트를 H에 복사

    for (k = 0; k < 4; k++) {

        L = copy(H, 100000);            //초기 리스트를 L에 복사

        QueryPerformanceCounter(&start);

        result = findKthSmallest(L, 100000, karray[k]); //결과값 저장

        QueryPerformanceCounter(&end);

        diff.QuadPart = end.QuadPart - start.QuadPart;

        printf("%d %.8lf \n", result, ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));  //결과, 시간 출력
    }

    free(L);
    free(H);

    return 0;
}

int* buildList(int n, int min, int max) {       //초기 리스트 생성 함수

    int* L;
    int i;

    L = (int*)malloc(sizeof(int) * (n + 1));
    if (L == NULL)
        return -1;

    for (i = 1; i <= n; i++) {
        L[i] = ((1 << 16) * rand()) % max + min;
    }
    // L[i] = (((rand() << 15) | rand()) % max) + min;   //랜덤값 저장

    return L;
}

void writeList(int* L, int n) {     //전체 요소 출력

    int i;

    for (i = 1; i <= n; i++)
        printf("%d ", L[i]);

    printf("\n");

}

int findKthSmallest(int* L, int n, int k) {     //k번째로 작은 값을 리턴하는 함수

    int i, del = 0;

    buildHeap(L, n);            //O(n) 시간

    for (i = 0; i < k; i++) {   //k번 반복
        del = removeMin(L, n);  //O(log(n)) 시간
        n -= 1;
    }                           // 따라서 O(n + k log(n)) 시간에 수행함

    return del;                 //k번째 작은 원소 반환
}

void buildHeap(int* L, int n) {     //상향식 힙 생성

    int i;

    for (i = n / 2; i >= 1; i--)
        downHeap(L, i, n);          //힙 속성 복구
}

void downHeap(int* L, int index, int n) {

    int son;

    if (index * 2 > n)      //자식 노드 없을 경우 리턴
        return;

    son = index * 2;

    if (index * 2 + 1 <= n) {
        if (L[index * 2 + 1] < L[index * 2])
            son = index * 2 + 1;
    }

    if (L[index] <= L[son]) //부모가 더 작으면 리턴
        return;

    swapElements(L, index, son);

    downHeap(L, son, n);
}

void swapElements(int* L, int index1, int index2) { //교환하는 함수

    int tmp;

    tmp = L[index1];
    L[index1] = L[index2];
    L[index2] = tmp;
}

int removeMin(int* L, int n) {  //루트를 반환하는 함수

    int key;

    key = L[1];
    L[1] = L[n];

    n -= 1;

    downHeap(L, 1, n);

    return key;
}

int* copy(int* L, int n) {  //리스트의 값을 복사하는 함수

    int* H;
    int i;

    H = (int*)malloc(sizeof(int) * (n + 1));
    if (H == NULL)
        return -1;

    for (i = 1; i <= n; i++)
        H[i] = L[i];

    return H;
}