#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable:4996)

typedef struct node {	//����
	int index;
	struct node* next;
}node;

typedef struct vertice {	//����
	node* adjacent;
	int id;
}vertice;

typedef struct edge {		//����
	int weight;
	int	start;
	int end;
	int id;
}edge;

typedef struct graph {		//�׷���
	vertice* vertices;
	edge* edges;
}graph;

graph g;
int m;					//������ ����

node* get_node(int i);
int opposite(node* k, int a);
void insert(int id, int a, int b);
void edgeMethod(int id, int a, int b, int w);
void buildGraph();
void printAdj(int a);
void modifyMethod(int a, int b, int w);
void removeMethod(int a, int b, int target);
void removeEdge(int a, int b, int target);

int main() {

	buildGraph();

	char command;
	int a, b, w, key;

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

	free(g.vertices);
	free(g.edges);

	return 0;
}

void buildGraph() {

	int i;

	g.vertices = (vertice*)malloc(sizeof(vertice) * 7);	//���� 1 ~ 6
	if (g.vertices == NULL)
		return -1;

	g.edges = (edge*)malloc(sizeof(edge) * 21);		//���� �ִ� 21��
	if (g.edges == NULL)
		return -1;

	//�������� �� ��������Ʈ ����� �ʱ�ȭ
	for (i = 1; i <= 6; i++) {
		g.vertices[i].id = i;
		g.vertices[i].adjacent = get_node(-1);
	}

	m = 0;

	edgeMethod(m++, 1, 2, 1);
	edgeMethod(m++, 1, 3, 1);
	edgeMethod(m++, 1, 4, 1);
	edgeMethod(m++, 1, 6, 2);
	edgeMethod(m++, 2, 3, 1);
	edgeMethod(m++, 3, 5, 4);
	edgeMethod(m++, 5, 5, 4);
	edgeMethod(m++, 5, 6, 3);

}

void edgeMethod(int id, int a, int b, int w) {

	g.edges[id].id = id;
	g.edges[id].start = a;
	g.edges[id].end = b;
	g.edges[id].weight = w;

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

void printAdj(int a) {

	if (a <= 0 || a > 6) {
		printf("-1\n");
		return;
	}

	int oppo, elem;

	node* head = g.vertices[a].adjacent;
	if (head == NULL)
		return -1;

	while (1) {

		elem = head->next->index;
		oppo = opposite(head->next, a);

		printf(" %d %d", g.vertices[oppo].id, g.edges[elem].weight);

		head = head->next;

		if (head->next == NULL)
			break;
	}
	printf("\n");
}

void modifyMethod(int a, int b, int w) {

	if (a <= 0 || a > 6 || b <= 0 || b > 6) {
		printf("-1\n");
		return;
	}

	//Ÿ�ٰ��� (a,b) ã��
	int target = -1, start, end;
	int i;

	if (a > b) {
		start = b;
		end = a;
	}
	else {
		start = a;
		end = b;
	}

	//Ÿ�� ���� �ε��� ã��
	for (i = 0; i < m; i++) {
		if (g.edges[i].id != -1 && g.edges[i].start == start && g.edges[i].end == end) {
			target = i;
			break;
		}
	}

	//������ �����ϴ� ���
	if (target != -1) {
		if (w == 0) {			//���� ����, w�� 0�̸� ����
			removeMethod(a, b, target);
			return;
		}
		else				//���� ����, w�� 0�� �ƴϸ� ����
			g.edges[target].weight = w;
	}
	//������ �������� �ʴ� ���
	else if (target == -1) {

		if (w == 0)			//�׳� ����
			return;

		else {					//���Ӱ� ����
			edgeMethod(m++, a, b, w);
			return;
		}
	}

}

void removeMethod(int a, int b, int target) {

	g.edges[target].id = -1;	//�������� ����

	removeEdge(a, b, target);

	if (a != b)
		removeEdge(b, a, target);

}

void removeEdge(int a, int b, int target) {

	node* node1 = g.vertices[a].adjacent->next;
	node* node2 = g.vertices[a].adjacent->next->next;

	while (1) {
		if (g.vertices[a].adjacent->next->index == target) {	//ù ���� �����ɶ� 

			free(g.vertices[a].adjacent->next);
			g.vertices[a].adjacent->next = node2;

			return;
		}
		else if (node2->index == target) {

			node1->next = node2->next;
			free(node2);

			return;
		}

		node1 = node1->next;
		node2 = node2->next;

		if (node1 == NULL)
			break;
	}
}

//������ �ݴ����� ��ȯ
int opposite(node* k, int a) {

	edge e = g.edges[k->index];

	if (e.start == a)
		return e.end;
	else
		return e.start;
}

void insert(int id, int a, int b) {

	node* k = g.vertices[a].adjacent;	//������ ���������� ���
	node* new = get_node(id);			//�ε��� id�� ����

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
