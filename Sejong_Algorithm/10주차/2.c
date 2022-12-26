#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable:4996)

typedef struct graph {
	int** adj;		//그래프 인접행렬
}graph;

graph g;

void buildgraph();
void printAdj(int key);
void modifyMethod(int a, int b, int w);
void edgeMethod(int a, int b, int w);

int main() {

	char command;
	int a, b, w, key;

	buildgraph();

	while (1) {
		scanf("%c", &command);

		if (command == 'a') {
			scanf("%d", &key);
			getchar();

			printAdj(key);
		}
		else if (command == 'm') {
			scanf("%d %d %d", &a, &b, &w);
			getchar();

			modifyMethod(a, b, w);
		}
		else if (command == 'q')
			break;
	}

	int i;

	for (i = 0; i < 7; i++) {
		free(g.adj[i]);
	}
	free(g.adj);

	return 0;
}

void buildgraph() {

	int i, j;

	g.adj = (int**)malloc(sizeof(int*) * 7);

	for (i = 0; i < 7; i++) {
		g.adj[i] = (int*)malloc(sizeof(int) * 7);
		for (j = 0; j < 7; j++) {
			g.adj[i][j] = 0;
		}
	}

	edgeMethod(1, 2, 1);
	edgeMethod(1, 3, 1);
	edgeMethod(1, 4, 1);
	edgeMethod(1, 6, 2);
	edgeMethod(2, 3, 1);
	edgeMethod(3, 5, 4);
	edgeMethod(5, 5, 4);
	edgeMethod(5, 6, 3);

}

void printAdj(int key) //출력
{
	if (key <= 0 || key > 6) {		//정점이 없을 경우
		printf("-1\n");
		return;
	}

	int i;

	for (i = 1; i < 7; i++) {
		if (g.adj[key][i]) {
			printf(" %d %d", i, g.adj[key][i]);
		}
	}
	printf("\n");
}

void modifyMethod(int a, int b, int w) {

	if (a <= 0 || a > 6 || b <= 0 || b > 6) {	//정점 없을 경우
		printf("-1\n");
		return;
	}

	if (w == 0) {				//간선 삭제
		g.adj[a][b] = 0;
		g.adj[b][a] = 0;
	}
	else {						//간선 존재하는지 체크
		if (g.adj[a][b] != 0) { //간선존재
			g.adj[a][b] = w;
			g.adj[b][a] = w;
		}
		else {
			edgeMethod(a, b, w);
		}
	}
}

void edgeMethod(int a, int b, int w) {

	g.adj[a][b] = w;
	g.adj[b][a] = w;
}