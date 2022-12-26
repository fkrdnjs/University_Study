#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable:4996)

typedef struct graph {
	int** adj;		//�׷��� �������
}graph;

graph g;
int n, m, s;

void buildgraph();
void edgeMethod(int a, int b);
void BFS(int s);
void enqueue(int k);
int dequeue();

int main() {

	buildgraph();
	BFS(s);

	for (int i = 0; i <= n; i++)
		free(g.adj[i]);
	free(g.adj);

	return 0;
}

void buildgraph() {

	int i, j;
	int a, b;

	scanf("%d %d %d", &n, &m, &s);

	g.adj = (int**)malloc(sizeof(int*) * (n + 1));
	if (g.adj == NULL)
		return -1;

	for (i = 0; i <= n; i++) {
		g.adj[i] = (int*)malloc(sizeof(int) * (n + 1));
		if (g.adj[i] == NULL)
			return -1;

		for (j = 0; j < n + 1; j++)
			g.adj[i][j] = 0;
	}

	for (i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		edgeMethod(a, b);
	}

}

int front = 0;
int rear = 0;
int* queue;

void enqueue(int k) {

	rear += 1;
	queue[rear] = k;

}

int dequeue() {

	front += 1;
	return queue[front];
}

void BFS(int s) {

	int* visit;
	int i;

	queue = (int*)malloc(sizeof(int) * (n + 1));
	if (queue == NULL)
		return -1;

	visit = (int*)malloc(sizeof(int) * (n + 1));
	if (visit == NULL)
		return -1;

	//visit �ʱ�ȭ
	for (i = 0; i < n + 1; i++)
		visit[i] = 0;

	visit[s] = 1;		//���� ������ �湮 üũ

	printf("%d\n", s);	//���� ���� ���

	enqueue(s);

	while (front != rear) {		//ť�� ������� ���� ���� �ݺ�
		s = dequeue();

		for (i = 1; i <= n; i++) {
			if (g.adj[s][i] == 1 && visit[i] == 0) {	//�湮���� �������

				visit[i] = 1; //�湮
				printf("%d\n", i);

				enqueue(i);
			}
		}
	}

	free(queue);
	free(visit);

}

void edgeMethod(int a, int b) {

	g.adj[a][b] = 1;
	g.adj[b][a] = 1;

}