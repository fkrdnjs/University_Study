#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<Windows.h>
#include<time.h>

#pragma warning(disable:4996)

int MAX = 30;

int A[30];	//항공 요금
int H[30];	//숙박 요금

int findmin(int a, int b);				//더 작은 값 찾는 함수
int airtel_bun(int n, int s, int d);	//분할통치
int rAirtel_bun(int s, int d);			//분할통치 재귀
int airtel_dong(int n, int s, int d);	//동적프로그래밍
int* m;									//동적프로그래밍에서 사용할 배열

int main() {

	int i;
	int n, s, d, mincost;
	int sd[3][2] = { {0,4},{2,5},{2,4} };
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	srand(time(NULL));
	QueryPerformanceFrequency(&ticksPerSec);

	A[0] = 0;										//항공료, 숙박비 초기화
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

		//분할통치--------------------------
		QueryPerformanceCounter(&start);
		mincost = airtel_bun(n, s, d);
		QueryPerformanceCounter(&end);

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("%3d%3d%3d  %8d    %s    %.8f\n", n, s, d, mincost, "DC", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);
		//동적프로그래밍------------------------------
		QueryPerformanceCounter(&start);
		mincost = airtel_dong(n, s, d);
		QueryPerformanceCounter(&end);

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("%3d%3d%3d  %8d    %s    %.8f\n", n, s, d, mincost, "DP", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

		free(m);	//동적프로그래밍 이후마다 m 프리해주기

	}

	n = MAX;
	s = 1;
	d = MAX - 2;

	//분할통치--------------------------
	QueryPerformanceCounter(&start);
	mincost = airtel_bun(n, s, d);
	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%3d%3d%3d  %8d    %s    %.8f\n", n, s, d, mincost, "DC", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

	//동적------------------------------
	QueryPerformanceCounter(&start);
	mincost = airtel_dong(n, s, d);
	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%3d%3d%3d  %8d    %s    %.8f\n", n, s, d, mincost, "DP", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

	free(m);	////동적프로그래밍 이후 m 프리
	return 0;
}

int findmin(int a, int b) {			//최소값 찾기

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

	if (s == d)					//출발지랑 목적지가 같으면 0 반환
		return 0;

	for (i = 0; i < d; i++) {

		if (i == s)		// 한 번에 갈 경우 숙박비 제외
			total = rAirtel_bun(s, i) + A[d - i];
		else
			total = rAirtel_bun(s, i) + H[i] + A[d - i];

		minimum = findmin(minimum, total);
	}

	return minimum;		//최소값 리턴

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

			if (j == s)		// 한 번에 갈 경우 숙박비 제외
				total = m[j] + A[i - j];
			else
				total = m[j] + H[j] + A[i - j];

			m[i] = findmin(m[i], total);
		}
	}

	return m[d];

}