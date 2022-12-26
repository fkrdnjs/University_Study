#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<Windows.h>
#include<time.h>

#pragma warning(disable:4996)

int MAX = 30;

int A[30];	//�װ� ���
int H[30];	//���� ���

int findmin(int a, int b);				//�� ���� �� ã�� �Լ�
int airtel_bun(int n, int s, int d);	//������ġ
int rAirtel_bun(int s, int d);			//������ġ ���
int airtel_dong(int n, int s, int d);	//�������α׷���
int* m;									//�������α׷��ֿ��� ����� �迭

int main() {

	int i;
	int n, s, d, mincost;
	int sd[3][2] = { {0,4},{2,5},{2,4} };
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	srand(time(NULL));
	QueryPerformanceFrequency(&ticksPerSec);

	A[0] = 0;										//�װ���, ���ں� �ʱ�ȭ
	A[1] = 1;

	for (i = 2; i < MAX; i++)
		A[i] = A[i - 1] + A[i - 1] % 5 + 3;

	H[0] = 0;
	H[1] = 5;

	for (i = 2; i < MAX; i++)
		H[i] = (H[i - 1] + i) % 9 + 1;

	printf("  n  s  d   mincost  version   cputime\n");

	n = 6;

	for (i = 0; i < 3; i++) {

		s = sd[i][0];
		d = sd[i][1];

		//������ġ--------------------------
		QueryPerformanceCounter(&start);
		mincost = airtel_bun(n, s, d);
		QueryPerformanceCounter(&end);

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("%3d%3d%3d  %8d    %s    %.8f\n", n, s, d, mincost, "DC", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);
		//�������α׷���------------------------------
		QueryPerformanceCounter(&start);
		mincost = airtel_dong(n, s, d);
		QueryPerformanceCounter(&end);

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("%3d%3d%3d  %8d    %s    %.8f\n", n, s, d, mincost, "DP", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

		free(m);	//�������α׷��� ���ĸ��� m �������ֱ�

	}

	n = MAX;
	s = 1;
	d = MAX - 2;

	//������ġ--------------------------
	QueryPerformanceCounter(&start);
	mincost = airtel_bun(n, s, d);
	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%3d%3d%3d  %8d    %s    %.8f\n", n, s, d, mincost, "DC", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

	//����------------------------------
	QueryPerformanceCounter(&start);
	mincost = airtel_dong(n, s, d);
	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%3d%3d%3d  %8d    %s    %.8f\n", n, s, d, mincost, "DP", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

	free(m);	////�������α׷��� ���� m ����
	return 0;
}

int findmin(int a, int b) {			//�ּҰ� ã��

	if (a < b)
		return a;
	else
		return b;

}

int airtel_bun(int n, int s, int d) {

	return rAirtel_bun(s, d);

}

int rAirtel_bun(int s, int d) {

	int minimum = 999999;
	int total = 0;
	int i;

	if (s == d)					//������� �������� ������ 0 ��ȯ
		return 0;

	for (i = 0; i < d; i++) {

		if (i == s)		// �� ���� �� ��� ���ں� ����
			total = rAirtel_bun(s, i) + A[d - i];
		else
			total = rAirtel_bun(s, i) + H[i] + A[d - i];

		minimum = findmin(minimum, total);
	}

	return minimum;		//�ּҰ� ����

}



int airtel_dong(int n, int s, int d) {

	int total = 0;
	int i, j;

	m = (int*)malloc(sizeof(int) * n);
	if (m == NULL)
		return -1;

	m[s] = 0;

	for (i = s + 1; i <= d; i++) {
		m[i] = 999999;

		for (j = s; j < i; j++) {

			if (j == s)		// �� ���� �� ��� ���ں� ����
				total = m[j] + A[i - j];
			else
				total = m[j] + H[j] + A[i - j];

			m[i] = findmin(m[i], total);
		}
	}

	return m[d];

}