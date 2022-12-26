#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)

typedef struct incident {
	int element;
	struct incident* next;
}incident;

typedef struct edge {
	int origin;
	int destination;
}edge;

typedef struct vertex {
	char name;
	incident* inedges;
	incident* outedges;
	int inDegree;
}vertex;

typedef struct graph {
	vertex* vertices;
	edge* edges;
}graph;

graph g;
int n, m;
int topOrder[100];
int queue[100];
int front, rear;

void initializegraph();
void buildgraph();
void insertvertex(char vName, int i);
void insertDirectededge(char uName, char wName, int i);
int index(char vName);
void addFirst(incident* H, int i);
void topologicalSort();
void initQueue();
int isEmpty();
void enqueue(int v);
int dequeue();

int main() {

	int i;

	buildgraph();

	topologicalSort();

	if (topOrder[0] == 0)
		printf("0\n");

	else {
		for (i = 1; i <= n; i++)
			printf("%c ", g.vertices[topOrder[i]].name);
	}

	for (i = 0; i < n; i++) {
		free(g.vertices[i].inedges);
		free(g.vertices[i].outedges);
	}

	free(g.vertices);
	free(g.edges);

	return 0;
}

void initializegraph() {

	g.vertices = (vertex*)malloc(sizeof(vertex) * 100);
	if (g.vertices == NULL)
		return;

	g.edges = (edge*)malloc(sizeof(edge) * 1000);
	if (g.edges == NULL)
		return;
}

void buildgraph() {

	int i;
	char vName, uName, wName;

	initializegraph();

	scanf("%d", &n);
	getchar();

	for (i = 0; i < n; i++) {
		scanf("%c", &vName);
		getchar();
		insertvertex(vName, i);
	}

	scanf("%d", &m);
	getchar();

	for (i = 0; i < m; i++) {
		scanf("%c %c", &uName, &wName);
		getchar();
		insertDirectededge(uName, wName, i);
	}
}

void insertvertex(char vName, int i) {

	g.vertices[i].name = vName;

	g.vertices[i].outedges = (incident*)malloc(sizeof(incident));
	if (g.vertices[i].outedges == NULL)
		return;

	g.vertices[i].inedges = (incident*)malloc(sizeof(incident));
	if (g.vertices[i].inedges == NULL)
		return;

	g.vertices[i].outedges->next = NULL;
	g.vertices[i].inedges->next = NULL;

	g.vertices[i].inDegree = 0;
}

void insertDirectededge(char uName, char wName, int i) {
	int u, w;

	u = index(uName);
	w = index(wName);

	g.edges[i].origin = u;
	g.edges[i].destination = w;

	addFirst(g.vertices[u].outedges, i);
	addFirst(g.vertices[w].inedges, i);

	g.vertices[w].inDegree++;
}

int index(char vName) {

	int i;

	for (i = 0; i < n; i++) {
		if (g.vertices[i].name == vName)
			return i;
	}

}

void addFirst(incident* H, int i) {

	incident* node = (incident*)malloc(sizeof(incident));
	if (node == NULL)
		return;

	node->element = i;
	node->next = H->next;
	H->next = node;
}

void topologicalSort() {

	int i;
	int in[100] = { 0 };
	int t, u, w;
	incident* e;

	initQueue();

	for (i = 0; i < n; i++) {
		in[i] = g.vertices[i].inDegree;
		if (in[i] == 0)
			enqueue(i);
	}

	t = 1;

	while (!isEmpty()) {
		u = dequeue();
		topOrder[t] = u;
		t += 1;

		e = g.vertices[u].outedges;
		e = e->next;
		while (e != NULL) {
			w = g.edges[e->element].destination;
			in[w] = in[w] - 1;

			if (in[w] == 0)
				enqueue(w);

			e = e->next;
		}
	}

	if (t <= n)
		topOrder[0] = 0;
	else
		topOrder[0] = 1;
}

void initQueue() {

	int i;

	front = 0;
	rear = 0;

	for (i = 0; i < 100; i++) {
		queue[i] = 0;
	}
}

int isEmpty() {

	if (front == rear)
		return 1;
	else
		return 0;
}

void enqueue(int v) {

	queue[rear] = v;
	rear = (rear + 1) % 100;

}

int dequeue() {

	int v;

	v = queue[front];

	front = (front + 1) % 100;

	return v;
}

