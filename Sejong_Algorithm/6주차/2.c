#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable:4996)

int find(int* x, int k, int left, int right);

int main() {

    int n, k, i, result;
    int* x;

    scanf("%d %d", &n, &k);

    x = (int*)malloc(sizeof(int) * n);		//배열 동적할당
    if (x == NULL)
        return -1;

    for (i = 0; i < n; i++)
        scanf("%d", &x[i]);

    if (k > x[n - 1])                       //x ≥ k를 만족하는 값이 없을 경우 n 출력
        printf(" %d", n);
    else {                                  //x ≥ k를 만족하는 값이 있을 경우
        result = find(x, k, 0, n - 1);

        printf(" %d", result);
    }
    free(x);								//배열 프리

    return 0;
}

int find(int* x, int k, int left, int right) {

    int mid;

    while (1) {

        mid = (left + right) / 2;       //가운데 인덱스

        if (x[mid] == k)                //가운데 값이 key와 일치할 경우 mid 반환
            return mid;
        if (left > right)               //left, right가 교차할 경우 left 반환
            return left;

        if (k < x[mid])                 //가운데 값보다 key가 작을 경우 right를 mid-1로 하고 반복
            right = mid - 1;
        else                            //가운데 값보다 key가 클 경우 elft를 mid+1로 하고 반복
            left = mid + 1;
    }

}