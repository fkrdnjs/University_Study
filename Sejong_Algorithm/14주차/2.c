#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable:4996)

typedef struct node {
	int index;
	struct node* next;
}node;

typedef struct vertice {
	int id;
	int d;
	int p;
	node* in;
	node* out;
}vertice;

typedef struct edge {
	int start;
	int end;
	int weight;
}edge;

typedef struct graph {
	vertice* vertices;
	edge* edges;
}graph;

graph g;
int n, m;

void buildgraph();
void edgeMethod(int id, int a, int b, int w);
void insert(node* header, int id);
int opposite(node* e, int a);
node* getnode(int i);

void bellman(int start);

int main() {

	int start;
	int i;

	scanf("%d %d %d", &n, &m, &start);

	buildgraph();

	bellman(start);

	for (i = 1; i <= n; i++) {
		if (g.vertices[i].p != -1)
			printf("%d %d\n", g.vertices[i].id, g.vertices[i].d);
	}

	free(g.vertices);
	free(g.edges);

	return 0;
}

void buildgraph() {

	int i;
	int start, end, weight;

	g.edges = (edge*)malloc(sizeof(edge) * m);
	if (g.edges == NULL)
		return;

	g.vertices = (vertice*)malloc(sizeof(vertice) * (n + 1));	//1บฮลอ
	if (g.vertices == NULL)
		return;

	for (i = 1; i <= n; i++) {
		g.vertices[i].id = i;
		g.vertices[i].out = getnode(-1);
		g.vertices[i].in = getnode(-1);
	}

	for (i = 0; i < m; i++) {
		scanf("%d %d %d", &start, &end, &weight);
		edgeMethod(i, start, end, weight);
	}

}

node* getnode(int i) {

	node* new = (node*)malloc(sizeof(node));

	new->index = i;
	new->next = NULL;

	return new;
}

void edgeMethod(int id, int a, int b, int w) {

	g.edges[id].start = a;
	g.edges[id].end = b;
	g.edges[id].weight = w;

	insert(g.vertices[a].out, id);
	insert(g.vertices[b].in, id);
}

void insert(node* header, int id) {

	node* new = getnode(id);

	while (header->next)
		header = header->next;

	header->next = new;

}

int opposite(node* e, int a) {

	edge k = g.edges[e->index];

	if (k.start == a)
		return k.end;
	else
		return k.start;
}

void bellman(int start) {

	int i, j;
	int u = -1;
	int z, e, weight = 0;
	node* k;

	for (i = 1; i <= n; i++) {
		g.vertices[i].d = 999999;
		g.vertices[i].p = -1;
	}

	g.vertices[start].d = 0;

	for (i = 1; i < n; i++) {
		for (j = 0; j < m; j++) {
			u = g.edges[j].start;
			z = g.edges[j].end;
			weight = g.edges[j].weight;

			if (g.vertices[u].d != 999999 && (g.vertices[u].d + weight) < g.vertices[z].d) {
				g.vertices[z].p = u;
				g.vertices[z].d = g.vertices[u].d + weight;
			}
		}
	}

}