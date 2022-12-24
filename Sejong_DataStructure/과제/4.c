#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>


typedef struct queue {                      //����ü ����
    int elem;
    struct queue* prev;
    struct queue* next;
}node;

int size = 0;                               //ť1�� ������
int size2 = 0;                              //ť2�� ������

node* front1 = NULL;                        //ť1�� ���� ��
node* rear1 = NULL;                         //ť1�� ���� ��

node* front2 = NULL;                        //ť2�� ���� ��
node* rear2 = NULL;                         //ť2�� ���� ��

node* tmp;                                  //�ּ� ��ȯ�� �� �ʿ��� �� �ּ�

int isEmpty() {                             //����ִ��� Ȯ���ϴ� �Լ� : ť2�� �׻� ����ֱ⿡ ť1�� ���� ��.
    if (size == 0)                          //��������� 0 ��ȯ
        return 0;
    else                                    //ä���������� 1 ��ȯ
        return 1;
}

int top() {                                 //���� �ֱٿ� �߰��� ���� ��ȯ�ϴ� �Լ� : ���������� �̿��� ����ð����� ����
    if (isEmpty() == 0) {                   //������� ��� �� ��ȯ
        return '\0';
    }
    else {                                  //ä���� ���� ��� ���� �� ��ȯ
        return front1->elem;
    }
}

void push1(int el) {                        //ť1�� push�ϴ� �Լ�

    node* new;

    new = (node*)malloc(sizeof(node));      //���ο� ��� ����
    if (new == NULL)
        return -1;

    if (size == 0) {                        //ù ���Ҹ� push�ϴ� ���
        new->elem = el;                     //elem�� �� �����ϰ� next, prev �η� �ʱ�ȭ
        new->next = NULL;
        new->prev = NULL;

        front1 = new;                       //���� ó���� �������� ����Ű�� ����
        rear1 = new;
    }
    else {                                  //ù ���Ұ� �ƴ� ���
        new->elem = el;
        new->prev = NULL;
        new->next = front1;                 //next�� ����Ʈ1 ���� 

        front1->prev = new;                 //����Ʈ1�� prev�� ���ο� ��忡 ����, ����Ʈ �� ĭ ������
        front1 = new;
    }

    size += 1;                              //ť1�� ������ ����
}

void push2(int el) {                        //ť2�� push�ϴ� �Լ� - push1�� ������ �ٸ��� ������ ����

    node* new;

    new = (node*)malloc(sizeof(node));      // ���ο� ��� ����
    if (new == NULL)
        return -1;

    if (size2 == 0) {                       //ó�� ������ ���
        new->elem = el;
        new->next = NULL;
        new->prev = NULL;

        front2 = new;
        rear2 = new;
    }
    else {                                  //ó�� ���Ұ� �ƴ� ���
        new->elem = el;
        new->prev = NULL;
        new->next = front2;

        front2->prev = new;
        front2 = new;
    }

    size2 += 1;                             //ť2�� ������ ����
}

void pushMillion() {                            //�鸸�� �߰��ϴ� �Լ�

    int i;

    srand(time(NULL));

    for (i = 0; i < 1000000; i++) {             //�鸸���� ���� �� ť1�� �߰�
        push1(rand() % 90 + 10);
    }

}

int popone() {                                  //�ϳ��� ��Ҹ� ���ְ� elem�� ��ȯ�ϴ� �Լ�
                                                //�Ʒ� pop�Լ��� �����ִ� �Լ�
    int k;

    k = rear1->elem;                            //k�� elem �� ����

    rear1 = rear1->prev;                       //���� �ڸ� �� ĭ ������ �̵�

    size -= 1;                                  //������ �ϳ� ����

    free(rear1->next);                          //����

    return k;                                   //������ �� ��ȯ
}

int pop() {                                    //popone�� �ݺ��Ͽ� ť1�� �ִ� ��ҵ��� 1���� ����� ť2�� �ű�� �Լ�

    int i;
    int k, z = 0;
    int sizehere = size;                        //�ʱ� size�� ���� : size ���� ��� ���ϱ� ����.

    if (isEmpty() == 0)                         //��������� �ٷ� ����
        return '\0';

    for (i = 0; i < sizehere - 1; i++) {        //�ϳ� ���� ť2�� �ű�� ����
        k = popone();                           //ť1�� �ִ� ��

        push2(k);                               //ť2�� ����
    }

    k = rear1->elem;                            //ť1�� �ϳ� �����ִ� �� ���� �� ���� 
    free(rear1);
    size -= 1;

    front1 = NULL;                              //�ʱ�ȭ
    rear1 = NULL;

    tmp = front1;                               //ť1�� ť2�� �ּ� & size �ٲٴ� ����
    front1 = front2;
    front2 = tmp;

    tmp = rear1;
    rear1 = rear2;
    rear2 = tmp;

    z = size;
    size = size2;
    size2 = z;

    return k;                                   //������ �� ��ȯ
}

char num[1000000] = { '\0' };                   //push�� ������ �� �� �־� ���ڿ��� �޾Ƽ� ����.

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
        scanf("%c", &command);                              //Ŀ�ǵ� �Է�
        getchar();

        if (command == 'S') {                               //S�� ��� isEmpty ȣ��

            QueryPerformanceCounter(&start);
            data = isEmpty();
            QueryPerformanceCounter(&end);

            diff.QuadPart = end.QuadPart - start.QuadPart;

            if (data == 0)                                  //������� ���
                printf("Empty");
            else                                            //���� ���
                printf("Nonempty");

            printf(" (%d), ", size);
            printf("cputime = %.10lf\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
        }
        else if (command == 't') {                          //top ȣ��

            QueryPerformanceCounter(&start);
            data = top();
            QueryPerformanceCounter(&end);

            diff.QuadPart = end.QuadPart - start.QuadPart;

            if (data == '\0')                               //������� ���
                printf("Empty Stack Exception!!");
            else                                            //���� ���
                printf("%d", data);

            printf(" (%d), ", size);
            printf("cputime = %.10lf\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
        }
        else if (command == 'p') {                                  //push1 ȣ��

            gets(num);                                              //���ڿ��� �Է� ����
            len = strlen(num);

            for (j = 0; j < len; j++) {                             //���ڿ� ���̸�ŭ �ݺ�
                result = 0;
                if (num[j] >= '0' && num[j] <= '9') {               //������ ���
                    while (1) {                                     //���ڰ� �� �ڸ��� �ƴ� ��� ó���ϴ� �ڵ�              
                        if (num[j] >= '0' && num[j] <= '9') {
                            result = result * 10 + (num[j] - '0');  //result�� ���� �����
                            j += 1;
                        }
                        else
                            break;
                    }
                }
                QueryPerformanceCounter(&start);
                push1(result);                                      //push1 �Լ� ȣ��
                QueryPerformanceCounter(&end);                      //�� ���� ����ð����� ����.
            }


            diff.QuadPart = end.QuadPart - start.QuadPart;

            printf("OK");
            printf(" (%d), ", size);
            printf("cputime = %.10lf\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

        }
        else if (command == 'P') {                              //pushMillion �Լ� ȣ��

            printf("OK");

            QueryPerformanceCounter(&start);
            pushMillion();
            QueryPerformanceCounter(&end);

            diff.QuadPart = end.QuadPart - start.QuadPart;

            printf(" (%d), ", size);
            printf("cputime = %.10lf\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
        }
        else if (command == 'o') {                              //pop�Լ� ȣ��

            QueryPerformanceCounter(&start);
            data = pop();
            QueryPerformanceCounter(&end);

            diff.QuadPart = end.QuadPart - start.QuadPart;

            if (data == '\0')                                   //��������� ���� ó��
                printf("Empty Stack Exception!!");
            else                                                //������ ���� ó��
                printf("%d", data);

            printf(" (%d), ", size);
            printf("cputime = %.10lf\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
        }
        else if (command == 'q') {                                //�Լ� ���� : �����ִ� ��ҵ� �������ְ� �����Ŵ

            p = front1;                                         //p�� ť1 ���� �� ����Ű���� �� - ť2�� pop�� �� �� ����� �׻� ����ִ� ����

            for (j = 0; j < size; j++) {                        //ť1 �������ִ� �ڵ�
                if (j == size - 1)                              //������ �κ��̸� �ٷ� ����
                    free(front1);
                else {                                          //������ �ƴ� ���
                    front1 = p->next;                           //����Ʈ�� �������� �ű�� 
                    free(p);                                    //p�� ������ �� p�� �ٽ� ����Ʈ ����Ű���� ��.
                    p = front1;
                }
            }
            return 0;
        }

    }

    return 0;

}