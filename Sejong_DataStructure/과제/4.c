#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>


typedef struct queue {                      //구조체 선언
    int elem;
    struct queue* prev;
    struct queue* next;
}node;

int size = 0;                               //큐1의 사이즈
int size2 = 0;                              //큐2의 사이즈

node* front1 = NULL;                        //큐1의 가장 앞
node* rear1 = NULL;                         //큐1의 가장 뒤

node* front2 = NULL;                        //큐2의 가장 앞
node* rear2 = NULL;                         //큐2의 가장 뒤

node* tmp;                                  //주소 교환할 때 필요한 빈 주소

int isEmpty() {                             //비어있는지 확인하는 함수 : 큐2는 항상 비어있기에 큐1만 보면 됨.
    if (size == 0)                          //비어있으면 0 반환
        return 0;
    else                                    //채워져있으면 1 반환
        return 1;
}

int top() {                                 //가장 최근에 추가된 변수 반환하는 함수 : 전역변수를 이용해 상수시간으로 구현
    if (isEmpty() == 0) {                   //비어있을 경우 널 반환
        return '\0';
    }
    else {                                  //채워져 있을 경우 원소 값 반환
        return front1->elem;
    }
}

void push1(int el) {                        //큐1에 push하는 함수

    node* new;

    new = (node*)malloc(sizeof(node));      //새로운 노드 생성
    if (new == NULL)
        return -1;

    if (size == 0) {                        //첫 원소를 push하는 경우
        new->elem = el;                     //elem에 값 저장하고 next, prev 널로 초기화
        new->next = NULL;
        new->prev = NULL;

        front1 = new;                       //가장 처음과 마지막을 가리키는 변수
        rear1 = new;
    }
    else {                                  //첫 원소가 아닌 경우
        new->elem = el;
        new->prev = NULL;
        new->next = front1;                 //next에 프론트1 대입 

        front1->prev = new;                 //프론트1의 prev를 새로운 노드에 연결, 프론트 한 칸 앞으로
        front1 = new;
    }

    size += 1;                              //큐1의 사이즈 증가
}

void push2(int el) {                        //큐2에 push하는 함수 - push1과 변수만 다르고 나머지 동일

    node* new;

    new = (node*)malloc(sizeof(node));      // 새로운 노드 생성
    if (new == NULL)
        return -1;

    if (size2 == 0) {                       //처음 원소일 경우
        new->elem = el;
        new->next = NULL;
        new->prev = NULL;

        front2 = new;
        rear2 = new;
    }
    else {                                  //처음 원소가 아닐 경우
        new->elem = el;
        new->prev = NULL;
        new->next = front2;

        front2->prev = new;
        front2 = new;
    }

    size2 += 1;                             //큐2의 사이즈 증가
}

void pushMillion() {                            //백만개 추가하는 함수

    int i;

    srand(time(NULL));

    for (i = 0; i < 1000000; i++) {             //백만개의 랜덤 수 큐1에 추가
        push1(rand() % 90 + 10);
    }

}

int popone() {                                  //하나의 요소를 없애고 elem값 반환하는 함수
                                                //아래 pop함수를 도와주는 함수
    int k;

    k = rear1->elem;                            //k에 elem 값 저장

    rear1 = rear1->prev;                       //가장 뒤를 한 칸 앞으로 이동

    size -= 1;                                  //사이즈 하나 감소

    free(rear1->next);                          //프리

    return k;                                   //저장한 값 반환
}

int pop() {                                    //popone을 반복하여 큐1에 있는 요소들을 1개만 남기고 큐2로 옮기는 함수

    int i;
    int k, z = 0;
    int sizehere = size;                        //초기 size값 저장 : size 값이 계속 변하기 때문.

    if (isEmpty() == 0)                         //비어있으면 바로 종료
        return '\0';

    for (i = 0; i < sizehere - 1; i++) {        //하나 빼고 큐2로 옮기는 과정
        k = popone();                           //큐1에 있는 값

        push2(k);                               //큐2에 저장
    }

    k = rear1->elem;                            //큐1에 하나 남아있던 값 저장 후 프리 
    free(rear1);
    size -= 1;

    front1 = NULL;                              //초기화
    rear1 = NULL;

    tmp = front1;                               //큐1과 큐2의 주소 & size 바꾸는 과정
    front1 = front2;
    front2 = tmp;

    tmp = rear1;
    rear1 = rear2;
    rear2 = tmp;

    z = size;
    size = size2;
    size2 = z;

    return k;                                   //삭제한 값 반환
}

char num[1000000] = { '\0' };                   //push를 여러개 할 수 있어 문자열로 받아서 저장.

int main(void)
{
    node* p = front1;
    char command;
    int i, j, data;
    int len, k, result = 0;
    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start, end, diff;

    QueryPerformanceFrequency(&ticksPerSec);

    while (1) {
        scanf("%c", &command);                              //커맨드 입력
        getchar();

        if (command == 'S') {                               //S일 경우 isEmpty 호출

            QueryPerformanceCounter(&start);
            data = isEmpty();
            QueryPerformanceCounter(&end);

            diff.QuadPart = end.QuadPart - start.QuadPart;

            if (data == 0)                                  //비어있을 경우
                printf("Empty");
            else                                            //있을 경우
                printf("Nonempty");

            printf(" (%d), ", size);
            printf("cputime = %.10lf\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
        }
        else if (command == 't') {                          //top 호출

            QueryPerformanceCounter(&start);
            data = top();
            QueryPerformanceCounter(&end);

            diff.QuadPart = end.QuadPart - start.QuadPart;

            if (data == '\0')                               //비어있을 경우
                printf("Empty Stack Exception!!");
            else                                            //있을 경우
                printf("%d", data);

            printf(" (%d), ", size);
            printf("cputime = %.10lf\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
        }
        else if (command == 'p') {                                  //push1 호출

            gets(num);                                              //문자열로 입력 받음
            len = strlen(num);

            for (j = 0; j < len; j++) {                             //문자열 길이만큼 반복
                result = 0;
                if (num[j] >= '0' && num[j] <= '9') {               //숫자일 경우
                    while (1) {                                     //숫자가 한 자리가 아닐 경우 처리하는 코드              
                        if (num[j] >= '0' && num[j] <= '9') {
                            result = result * 10 + (num[j] - '0');  //result에 숫자 저장됨
                            j += 1;
                        }
                        else
                            break;
                    }
                }
                QueryPerformanceCounter(&start);
                push1(result);                                      //push1 함수 호출
                QueryPerformanceCounter(&end);                      //한 번의 실행시간만을 측정.
            }


            diff.QuadPart = end.QuadPart - start.QuadPart;

            printf("OK");
            printf(" (%d), ", size);
            printf("cputime = %.10lf\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

        }
        else if (command == 'P') {                              //pushMillion 함수 호출

            printf("OK");

            QueryPerformanceCounter(&start);
            pushMillion();
            QueryPerformanceCounter(&end);

            diff.QuadPart = end.QuadPart - start.QuadPart;

            printf(" (%d), ", size);
            printf("cputime = %.10lf\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
        }
        else if (command == 'o') {                              //pop함수 호출

            QueryPerformanceCounter(&start);
            data = pop();
            QueryPerformanceCounter(&end);

            diff.QuadPart = end.QuadPart - start.QuadPart;

            if (data == '\0')                                   //비어있으면 예외 처리
                printf("Empty Stack Exception!!");
            else                                                //있으면 정상 처리
                printf("%d", data);

            printf(" (%d), ", size);
            printf("cputime = %.10lf\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
        }
        else if (command == 'q') {                                //함수 종료 : 남아있는 요소들 프리해주고 종료시킴

            p = front1;                                         //p가 큐1 제일 앞 가리키도록 함 - 큐2는 pop을 할 때 말고는 항상 비어있는 상태

            for (j = 0; j < size; j++) {                        //큐1 프리해주는 코드
                if (j == size - 1)                              //마지막 부분이면 바로 프리
                    free(front1);
                else {                                          //마지막 아닐 경우
                    front1 = p->next;                           //프론트를 다음으로 옮기고 
                    free(p);                                    //p를 프리한 후 p가 다시 프론트 가리키도록 함.
                    p = front1;
                }
            }
            return 0;
        }

    }

    return 0;

}