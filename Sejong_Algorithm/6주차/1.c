#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable:4996)

int rfind(int* x, int k, int left, int right);

int main() {

	int n, k, i, result;
	int* x;

	scanf("%d %d", &n, &k);

	x = (int*)malloc(sizeof(int) * n);		//�迭 �����Ҵ�
	if (x == NULL)
		return -1;

	for (i = 0; i < n; i++)
		scanf("%d", &x[i]);

	if (k < x[0])							//x �� k �� �����ϴ� ���� ���� ��� -1 ���
		printf(" -1");
	else {									//�����ϴ� k ���� ��� rfind ȣ��
		result = rfind(x, k, 0, n - 1);

		printf(" %d", result);
	}

	free(x);								//�迭 ����

	return 0;
}

int rfind(int* x, int k, int left, int right) {

	if (left > right)				//�����ϸ� right ��ȯ
		return right;

	int mid;

	mid = (left + right) / 2;		//����� ����

	if (k == x[mid])				//mid�� key�� ��ġ�ϸ� mid ��ȯ
		return mid;
	else if (k < x[mid])			//key�� �� ������ ���� �κ����� ���
		rfind(x, k, left, mid - 1);
	else							//key�� �� ũ�� ������ �κ����� ���
		rfind(x, k, mid + 1, right);
}