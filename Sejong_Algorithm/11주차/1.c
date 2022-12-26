#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable:4996)

typedef struct node {	//인접
	int index;
	struct node* next;
}node;

typedef struct vertice {	//정점
	node* adjacent;
	int id;
	int visited;
}vertice;

typedef struct edge {		//간선
	int	start;
	int end;
	int id;
}edge;

typedef struct graph {		//그래프
	vertice* vertices;
	edge* edges;
}graph;

graph g;
int n, m, s;

node* get_node(int i);
int opposite(node* k, int a);
void insert(int id, int a, int b);
void edgeMethod(int id, int a, int b);
void buildGraph();
void DFS(int init);

int main() {

	buildGraph();
	DFS(s);

	free(g.vertices);
	free(g.edges);

	return 0;
}

void buildGraph() {

	int i;
	int a, b;

	scanf("%d %d %d", &n, &m, &s);

	g.vertices = (vertice*)malloc(sizeof(vertice) * (n + 1));
	if (g.vertices == NULL)
		return -1;

	g.edges = (edge*)malloc(sizeof(edge) * m);
	if (g.edges == NULL)
		return -1;

	for (i = 1; i <= n; i++) {
		g.vertices[i].id = i;
		g.vertices[i].visited = 0;				//방문여부 0으로 초기화
		g.vertices[i].adjacent = get_node(-1);
	}

	for (i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		edgeMethod(i, a, b);
	}

}

void DFS(int init) {

	g.vertices[init].visited = 1;

	printf("%d\n", g.vertices[init].id);

	node* k = g.vertices[init].adjacent;

	int oppo;

	while (k->next != NULL) {
		oppo = opposite(k->next, init);

		if (g.vertices[oppo].visited == 0)
			DFS(oppo);

		k = k->next;
	}

}

void edgeMethod(int id, int a, int b) {

	g.edges[id].id = id;
	g.edges[id].start = a;
	g.edges[id].end = b;

	insert(id, a, b);

	if (a != b) {
		insert(id, b, a);
	}
}

node* get_node(int i) {

	node* new = (node*)malloc(sizeof(node));
	if (new == NULL)
		return -1;

	new->index = i;
	new->next = NULL;

	return new;
}

//간선의 반대정점 반환
int opposite(node* k, int a) {

	edge e = g.edges[k->index];

	if (e.start == a)
		return e.end;
	else
		return e.start;
}

void insert(int id, int a, int b) {

	node* k = g.vertices[a].adjacent;	//삽입할 부착간선의 헤드
	node* new = get_node(id);			//인덱스 id번 간선

	int v1, v2;

	if (k->next == NULL)
		g.vertices[a].adjacent->next = new;

	else {
		while (1) {

			v1 = opposite(k->next, a);

			if (v1 > b) {
				new->next = k->next;
				g.vertices[a].adjacent->next = new;
				return;
			}
			else if (k->next->next != NULL) {
				v2 = opposite(k->next->next, a);

				if (v2 > b) {
					new->next = k->next->next;
					k->next->next = new;
					return;
				}
			}

			k = k->next;

			if (k->next == NULL)
				break;
		}
	}

	k->next = new;
}
