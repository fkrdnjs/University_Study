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
		scanf("%c", &answer);			//Y, N 입력

		mid = (a + b) / 2;				//mid는 가운데 값

		if (answer == 'Y')				//Y일 경우 범위를 a를 mid + 1로 변경
			a = mid + 1;
		else							//N일 경우 b를 mid로 변경
			b = mid;
	}

	printf("%d", b);					//반복문 다 돌면 b 출력

	return 0;
}