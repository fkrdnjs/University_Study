#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

/* 연결리스트를 이용해서 해결했습니다*/

int size = 0;                                   //스택 전체 개수 세는 전역변수

typedef struct stack {                          //연결리스트로 스택 구현

    int el;
    struct stack* next;
    int min;

}stack;

stack* top = NULL;                              //제일 앞 스택 가리키는 전역변수top

void push(int elem) {                           //하나 추가하는 함수
    stack* new;

    new = (stack*)malloc(sizeof(stack));        //새로운 리스트 추가
    if (new == NULL)
        return -1;

    if (size == 0)                              //가장 처음 요소일 경우 min에 elem값 넣어주기
        new->min = elem;
    else {
        if (elem < top->min)                    //이전 최소값과 비교해서 추가하는 원소값이 더 작을 경우 min값 변경
            new->min = elem;
        else                                    //추가하는 원소값이 더 클 경우 min값 유지
            new->min = top->min;
    }

    new->el = elem;                             //값 넣고
    new->next = top;                            //top으로 연결
    top = new;                                  //top을 new로 변경해서 가장 앞을 가리키도록 한다.

    size += 1;                                  //전체 크기 1 증가

}

int pop() {                                     //하나 삭제하는 함수

    stack* p = top;                             //p가 top 가리키도록
    int result;

    if (size == 0)                              // 원소가 하나도 없을 경우 널 값 반환하고 종료
        return '\0';

    else {                                      //삭제할 원소 있을 경우
        result = p->el;
        top = p->next;                          //top을 두 번째 원소 가리키도록 한다.

        free(p);                                //가장 앞에 있는 원소 프리

        size -= 1;

        return result;
    }
}

int findMin() {                                 //최소값 찾는 함수 : 상수시간

    if (size == 0)                              //원소가 없으면 널값 반환
        return '\0';

    else {
        return top->min;                                 //최소값 반환
    }
}

void pushMillion() {                            //1000000개 추가하는 함수

    int i;

    srand(time(NULL));

    for (i = 0; i < 1000000; i++) {             //난수함수 사용해서 추가
        push(rand() % 9000 + 1000);             //push 함수 반복 호출
    }

}

int popMillion() {                              //1000000개 제거하는 함수

    int i;

    if (size >= 1000000) {                     //원소 개수가 충분할 경우 삭제 진행
        for (i = 0; i < 1000000; i++) {
            pop();                              //pop 반복 호출
        }
        return 1;
    }
    else {                                      //원소가 충분하지 않을 경우 0 반환
        return 0;
    }
}

void freehelp() {                               //프로그램 종료시 스택 전부 프리해주는 함수

    int i;
    stack* p = top;

    for (i = 0; i < size; i++) {                //size만큼 반복하면서 free
        if (i == size - 1)                      //마지막 원소일 경우 바로 free
            free(top);
        else {                                  //마지막 원소가 아닐 경우
            top = p->next;
            free(p);
            p = top;
        }
    }

}

int main(void)
{
    int elem;
    char command;
    int min, k;
    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start, end, diff;

    QueryPerformanceFrequency(&ticksPerSec);

    while (1) {
        scanf("%c", &command);                                  //수행할 함수 커맨드 입력
        getchar();

        if (command == 'p') {
            scanf("%d", &elem);
            getchar();

            QueryPerformanceCounter(&start);
            push(elem);                                         //push함수 호출
            QueryPerformanceCounter(&end);

            printf("push ");                                    //함수명, 추가한 원소, 사이즈, 실행 시간 출력
            printf("%d ", elem);
            printf("(%d), ", size);

            diff.QuadPart = end.QuadPart - start.QuadPart;
            printf("cputime = %.10lf", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
        }

        else if (command == 'P') {

            QueryPerformanceCounter(&start);
            pushMillion();                                      //pushMillion함수 호출
            QueryPerformanceCounter(&end);

            printf("pushMillion ");                             //함수명, 사이즈, 실행 시간 출력
            printf("(%d), ", size);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            printf("cputime = %.10lf", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
        }

        else if (command == 'o') {

            QueryPerformanceCounter(&start);
            k = pop();                                          //pop 함수 호출
            QueryPerformanceCounter(&end);

            printf("pop ");

            if (k == '\0')                                      //스택에 값이 하나도 없으면 오류 문구 출력
                printf("No Element ");
            else                                                //삭제 실행된 경우 삭제한 원소값 출력
                printf("%d ", k);

            printf("(%d), ", size);                             //사이즈, 실행시간 출력
            diff.QuadPart = end.QuadPart - start.QuadPart;
            printf("cputime = %.10lf", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
        }

        else if (command == 'O') {

            QueryPerformanceCounter(&start);
            k = popMillion();                                   //popMillion 함수 호출
            QueryPerformanceCounter(&end);

            printf("popMillion ");
            if (k == 0)                                         //0일 경우 오류 문구 출력
                printf("Not Enough");

            printf("(%d), ", size);                             //사이즈, 실행시간 출력
            diff.QuadPart = end.QuadPart - start.QuadPart;
            printf("cputime = %.10lf", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
        }

        else if (command == 'f') {

            QueryPerformanceCounter(&start);
            min = findMin();                                    //findMin함수 호출
            QueryPerformanceCounter(&end);

            printf("min ");                                     //함수명, 최소값, 사이즈, 실행 시간 출력

            if (min == '\0')                                      //스택에 값이 하나도 없으면 오류 문구 출력
                printf("No Element ");
            else                                                //최소값 출력
                printf("%d ", min);

            printf("(%d), ", size);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            printf("cputime = %.10lf", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
        }

        else if (command == 'q') {
            freehelp();                                         //freehelp함수 호출 후 종료
            printf("(프로그램 종료)");
            return 0;
        }

        printf("\n");
    }

    return 0;
}
