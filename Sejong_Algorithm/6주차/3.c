#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable:4996)

int main() {

	int a, b, cnt, i;
	int mid;
	char answer;

	scanf("%d %d %d", &a, &b, &cnt);
	getchar();

	for (i = 0; i < cnt; i++) {
		scanf("%c", &answer);			//Y, N �Է�

		mid = (a + b) / 2;				//mid�� ��� ��

		if (answer == 'Y')				//Y�� ��� ������ a�� mid + 1�� ����
			a = mid + 1;
		else							//N�� ��� b�� mid�� ����
			b = mid;
	}

	printf("%d", b);					//�ݺ��� �� ���� b ���

	return 0;
}