#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable:4996)

int rfind(int* x, int k, int left, int right);

int main() {

	int n, k, i, result;
	int* x;

	scanf("%d %d", &n, &k);

	x = (int*)malloc(sizeof(int) * n);		//배열 동적할당
	if (x == NULL)
		return -1;

	for (i = 0; i < n; i++)
		scanf("%d", &x[i]);

	if (k < x[0])							//x ≤ k 를 만족하는 값이 없을 경우 -1 출력
		printf(" -1");
	else {									//만족하는 k 있을 경우 rfind 호출
		result = rfind(x, k, 0, n - 1);

		printf(" %d", result);
	}

	free(x);								//배열 프리

	return 0;
}

int rfind(int* x, int k, int left, int right) {

	if (left > right)				//교차하면 right 반환
		return right;

	int mid;

	mid = (left + right) / 2;		//가운데값 설정

	if (k == x[mid])				//mid와 key가 일치하면 mid 반환
		return mid;
	else if (k < x[mid])			//key가 더 작으면 왼쪽 부분으로 재귀
		rfind(x, k, left, mid - 1);
	else							//key가 더 크면 오른쪽 부분으로 재귀
		rfind(x, k, mid + 1, right);
}