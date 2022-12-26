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
	node* adjacent;
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

typedef struct queue {
	int size;
	int max;
	int* key;
	int* value;
}queue;

queue q;
graph g;
int n, m;

void buildgraph();
void edgeMethod(int id, int a, int b, int w);
void insert(int id, int a, int b);
int opposite(node* e, int a);
node* getnode(int i);

int isEmpty();
void initqueue();
int dequeue();
void enqueue(int key, int value);
int find(int obj);
void replaceKey(int obj, int key);
void dijkstra(int s);

int main() {

	int start;
	int i;

	scanf("%d %d %d", &n, &m, &start);

	buildgraph();

	dijkstra(start);

	for (i = 1; i <= n; i++) {
		if (g.vertices[i].p != -1)
			printf("%d %d\n", g.vertices[i].id, g.vertices[i].d);
	}

	free(g.vertices);
	free(g.edges);
	free(q.key);
	free(q.value);

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
		g.vertices[i].adjacent = getnode(-1);
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

	insert(id, a, b);

	if (a != b)
		insert(id, b, a);
}

void insert(int id, int a, int b) {

	node* header = g.vertices[a].adjacent;
	node* new;

	while (header->next)
		header = header->next;

	new = getnode(id);
	header->next = new;
}

int opposite(node* e, int a) {

	edge k = g.edges[e->index];

	if (k.start == a)
		return k.end;
	else
		return k.start;
}

void initqueue() {

	q.max = n;
	q.size = 0;

	q.key = (int*)malloc(sizeof(int) * n);
	if (q.key == NULL)
		return;

	q.value = (int*)malloc(sizeof(int) * n);
	if (q.value == NULL)
		return;
}

int dequeue() {

	int mink, minv, index;
	int i;

	mink = q.key[0];
	minv = q.value[0];
	index = 0;

	for (i = 1; i < q.max; i++) {
		if (q.key[i] < mink) {
			mink = q.key[i];
			minv = q.value[i];
			index = i;
		}
	}

	q.key[index] = 999999;
	q.value[index] = -1;
	q.size -= 1;

	return minv;

}

void enqueue(int key, int value) {

	int index;

	index = q.size;

	q.key[index] = key;
	q.value[index] = value;

	q.size += 1;
}

int isEmpty() {

	if (q.size == 0)
		return 1;
	else
		return 0;
}

int find(int obj) {

	int i;

	for (i = 0; i < q.max; i++) {
		if (q.value[i] == obj)
			return 1;
	}

	return 0;
}

void replaceKey(int obj, int key) {

	int i;

	for (i = 0; i < q.max; i++) {
		if (q.value[i] == obj)
			q.key[i] = key;
	}
}

void dijkstra(int s) {

	int i;
	int u = -1;
	int z, e;

	for (i = 1; i <= n; i++) {
		g.vertices[i].d = 999999;
		g.vertices[i].p = -1;
	}

	g.vertices[s].d = 0;

	initqueue();

	for (i = 1; i <= n; i++)
		enqueue(g.vertices[i].d, i);

	node* k;

	while (!isEmpty()) {
		u = dequeue();

		if (u == -1)
			break;

		k = g.vertices[u].adjacent;

		while (k->next) {
			z = opposite(k->next, u);

			e = k->next->index;

			if (find(z) && (g.edges[e].weight + g.vertices[u].d) < g.vertices[z].d) {
				g.vertices[z].p = u;
				g.vertices[z].d = g.edges[e].weight + g.vertices[u].d;
				replaceKey(z, g.vertices[z].d);
			}

			k = k->next;
		}
	}

}