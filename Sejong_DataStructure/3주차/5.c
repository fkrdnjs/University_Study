#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void hanoi(int n, char from, char mid, char to) {

    if (n == 1) {
        printf("%c %c\n", from, to);
        return 0;
    }

    hanoi(n - 1, from, to, mid);//���ۿ��� �������� ���� �������� �ű��
    printf("%c %c\n", from, to);

    hanoi(n - 1, mid, from, to);//�������� �ִ°� ���������� �������� �ű��

}

int main(void)
{
    int n;

    scanf("%d", &n);

    hanoi(n, 'A', 'B', 'C');

    return 0;
}
