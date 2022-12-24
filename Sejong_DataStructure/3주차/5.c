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

    hanoi(n - 1, from, to, mid);//시작에서 목적지를 거쳐 경유지에 옮기기
    printf("%c %c\n", from, to);

    hanoi(n - 1, mid, from, to);//경유지에 있는걸 시작을거쳐 목적지로 옮기기

}

int main(void)
{
    int n;

    scanf("%d", &n);

    hanoi(n, 'A', 'B', 'C');

    return 0;
}
