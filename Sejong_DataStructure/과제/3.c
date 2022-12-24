#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

/* ���Ḯ��Ʈ�� �̿��ؼ� �ذ��߽��ϴ�*/

int size = 0;                                   //���� ��ü ���� ���� ��������

typedef struct stack {                          //���Ḯ��Ʈ�� ���� ����

    int el;
    struct stack* next;
    int min;

}stack;

stack* top = NULL;                              //���� �� ���� ����Ű�� ��������top

void push(int elem) {                           //�ϳ� �߰��ϴ� �Լ�
    stack* new;

    new = (stack*)malloc(sizeof(stack));        //���ο� ����Ʈ �߰�
    if (new == NULL)
        return -1;

    if (size == 0)                              //���� ó�� ����� ��� min�� elem�� �־��ֱ�
        new->min = elem;
    else {
        if (elem < top->min)                    //���� �ּҰ��� ���ؼ� �߰��ϴ� ���Ұ��� �� ���� ��� min�� ����
            new->min = elem;
        else                                    //�߰��ϴ� ���Ұ��� �� Ŭ ��� min�� ����
            new->min = top->min;
    }

    new->el = elem;                             //�� �ְ�
    new->next = top;                            //top���� ����
    top = new;                                  //top�� new�� �����ؼ� ���� ���� ����Ű���� �Ѵ�.

    size += 1;                                  //��ü ũ�� 1 ����

}

int pop() {                                     //�ϳ� �����ϴ� �Լ�

    stack* p = top;                             //p�� top ����Ű����
    int result;

    if (size == 0)                              // ���Ұ� �ϳ��� ���� ��� �� �� ��ȯ�ϰ� ����
        return '\0';

    else {                                      //������ ���� ���� ���
        result = p->el;
        top = p->next;                          //top�� �� ��° ���� ����Ű���� �Ѵ�.

        free(p);                                //���� �տ� �ִ� ���� ����

        size -= 1;

        return result;
    }
}

int findMin() {                                 //�ּҰ� ã�� �Լ� : ����ð�

    if (size == 0)                              //���Ұ� ������ �ΰ� ��ȯ
        return '\0';

    else {
        return top->min;                                 //�ּҰ� ��ȯ
    }
}

void pushMillion() {                            //1000000�� �߰��ϴ� �Լ�

    int i;

    srand(time(NULL));

    for (i = 0; i < 1000000; i++) {             //�����Լ� ����ؼ� �߰�
        push(rand() % 9000 + 1000);             //push �Լ� �ݺ� ȣ��
    }

}

int popMillion() {                              //1000000�� �����ϴ� �Լ�

    int i;

    if (size >= 1000000) {                     //���� ������ ����� ��� ���� ����
        for (i = 0; i < 1000000; i++) {
            pop();                              //pop �ݺ� ȣ��
        }
        return 1;
    }
    else {                                      //���Ұ� ������� ���� ��� 0 ��ȯ
        return 0;
    }
}

void freehelp() {                               //���α׷� ����� ���� ���� �������ִ� �Լ�

    int i;
    stack* p = top;

    for (i = 0; i < size; i++) {                //size��ŭ �ݺ��ϸ鼭 free
        if (i == size - 1)                      //������ ������ ��� �ٷ� free
            free(top);
        else {                                  //������ ���Ұ� �ƴ� ���
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
        scanf("%c", &command);                                  //������ �Լ� Ŀ�ǵ� �Է�
        getchar();

        if (command == 'p') {
            scanf("%d", &elem);
            getchar();

            QueryPerformanceCounter(&start);
            push(elem);                                         //push�Լ� ȣ��
            QueryPerformanceCounter(&end);

            printf("push ");                                    //�Լ���, �߰��� ����, ������, ���� �ð� ���
            printf("%d ", elem);
            printf("(%d), ", size);

            diff.QuadPart = end.QuadPart - start.QuadPart;
            printf("cputime = %.10lf", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
        }

        else if (command == 'P') {

            QueryPerformanceCounter(&start);
            pushMillion();                                      //pushMillion�Լ� ȣ��
            QueryPerformanceCounter(&end);

            printf("pushMillion ");                             //�Լ���, ������, ���� �ð� ���
            printf("(%d), ", size);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            printf("cputime = %.10lf", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
        }

        else if (command == 'o') {

            QueryPerformanceCounter(&start);
            k = pop();                                          //pop �Լ� ȣ��
            QueryPerformanceCounter(&end);

            printf("pop ");

            if (k == '\0')                                      //���ÿ� ���� �ϳ��� ������ ���� ���� ���
                printf("No Element ");
            else                                                //���� ����� ��� ������ ���Ұ� ���
                printf("%d ", k);

            printf("(%d), ", size);                             //������, ����ð� ���
            diff.QuadPart = end.QuadPart - start.QuadPart;
            printf("cputime = %.10lf", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
        }

        else if (command == 'O') {

            QueryPerformanceCounter(&start);
            k = popMillion();                                   //popMillion �Լ� ȣ��
            QueryPerformanceCounter(&end);

            printf("popMillion ");
            if (k == 0)                                         //0�� ��� ���� ���� ���
                printf("Not Enough");

            printf("(%d), ", size);                             //������, ����ð� ���
            diff.QuadPart = end.QuadPart - start.QuadPart;
            printf("cputime = %.10lf", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
        }

        else if (command == 'f') {

            QueryPerformanceCounter(&start);
            min = findMin();                                    //findMin�Լ� ȣ��
            QueryPerformanceCounter(&end);

            printf("min ");                                     //�Լ���, �ּҰ�, ������, ���� �ð� ���

            if (min == '\0')                                      //���ÿ� ���� �ϳ��� ������ ���� ���� ���
                printf("No Element ");
            else                                                //�ּҰ� ���
                printf("%d ", min);

            printf("(%d), ", size);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            printf("cputime = %.10lf", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
        }

        else if (command == 'q') {
            freehelp();                                         //freehelp�Լ� ȣ�� �� ����
            printf("(���α׷� ����)");
            return 0;
        }

        printf("\n");
    }

    return 0;
}
