#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct vertices {
    char e;
    int d;
    int count; // 현재 이 정점으로 갈 수 있는 경로의 수를 저장
    struct vertices* left, * right;
}vertices;

typedef struct incidence {
    struct incidence* down, * next;
}incidence;

typedef struct edges {
    int w;
    struct edges* left, * right;
    struct edges* next;
}edges;

typedef struct queue {
    vertices* v;
    struct queue* next, * prev;
}queue;

queue* Q = NULL, * rear = NULL;
vertices* head = NULL;
edges* header = NULL;

void makeVertex(char ee) {
    vertices* newnode = NULL;
    newnode = (vertices*)malloc(sizeof(vertices));
    newnode->e = ee;
    newnode->left = NULL;
    newnode->right = NULL;

    vertices* p = head;

    if (head == NULL) {
        head = newnode;
    }
    else {
        while (p->right != NULL) {
            p = p->right;
        }
        p->right = newnode;
    }

}

void makeEdges(char leftn, char rightn, int weight) {
    edges* newnode;
    newnode = (edges*)malloc(sizeof(edges));
    newnode->w = weight; // add weight
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->next = NULL; // 간선 초기화

    if (header == NULL) {
        header = newnode;
    }
    else {
        edges* t = header;
        while (t->next != NULL) {
            t = t->next;
        }
        t->next = newnode;
    } // 새간선을 간선리스트에 붙임

    vertices* p = head; // p는 꼭짓점
    while (p != NULL) {



        if (p->e == leftn) {
            incidence* newline = (incidence*)malloc(sizeof(incidence));
            newnode->left = p;

            newline->down = NULL;
            newline->next = NULL;
            int cnt = 0;
            // 간선의 왼쪽을 등록
            if (p->left == NULL) { // p에 아무 간선도 등록안되어 있으면
                p->left = newline; // 꼭짓점에 부착간선 붙이고
            }
            else { // 아니라면 부착간선을 작은 순서대로 넣어준다
                incidence* tmp = p->left; // tmp는 부착간선
                while (tmp != NULL) {
                    edges* sequence = tmp->down;
                    // 이번 순번의 부착간선의 간선에 달린 꼭짓점의 계수를 알아보기
                    vertices* fAnswer = sequence->left;
                    vertices* sAnswer = sequence->right;
                    if (fAnswer->e == leftn) {
                        char correct = sAnswer->e; // 계수 찾음
                        if (correct > rightn) {
                            // 지금 연결하려는 상대 꼭짓점 보다 지금 찾은 계수의 값이 
                            // 더 크면 앞쪽에 붙여야 하므로 부착 간선을 붙여준다
                            if (tmp == p->left) { // 이것이 첫 부착간선의 앞에 가야 한다면
                                newline->next = p->left;
                                p->left = newline;
                                break;
                            }
                            else {
                                incidence* past = p->left;
                                while (1) {
                                    if (past->next == tmp) {
                                        break;
                                    }
                                    past = past->next;
                                }
                                newline->next = tmp;
                                past->next = newline;
                                break;
                            } // 아니라면 사이에 껴준다
                            cnt++; // 등록이 됐다면 올려준다
                        }

                    }
                    else if (sAnswer->e == leftn) {
                        char correct = fAnswer->e; // 계수 찾음
                        if (correct > rightn) {
                            // 지금 연결하려는 상대 꼭짓점 보다 지금 찾은 계수의 값이 
                            // 더 크면 앞쪽에 붙여야 하므로 부착 간선을 붙여준다
                            if (tmp == p->left) { // 이것이 첫 부착간선의 앞에 가야 한다면
                                newline->next = p->left;
                                p->left = newline;
                                break;
                            }
                            else {
                                incidence* past = p->left;
                                while (1) {
                                    if (past->next == tmp) {
                                        break;
                                    }
                                    past = past->next;
                                }
                                newline->next = tmp;
                                past->next = newline;
                                break;
                            } // 아니라면 사이에 껴준다
                            cnt++; // 등록이 됐다면 올려준다
                        }

                    }
                    if (tmp->next == NULL && cnt == 0) {
                        tmp->next = newline;
                        break;
                    }
                    tmp = tmp->next;
                }
            }
            newline->down = newnode; // 마지막으로 부착간선을 간선에 붙인다
        }




        else if (p->e == rightn) {
            incidence* newline = (incidence*)malloc(sizeof(incidence)); // 꼭짓점
            newnode->right = p;
            // 간선의 오른쪽을 등록

            newline->down = NULL;
            newline->next = NULL;
            int cnt = 0;
            // 간선의 오른쪽을 등록
            if (p->left == NULL) { // p에 아무 간선도 등록안되어 있으면
                p->left = newline; // 꼭짓점에 부착간선 붙이고
            }
            else { // 아니라면 부착간선을 작은 순서대로 넣어준다
                incidence* tmp = p->left; // tmp는 부착간선
                while (tmp != NULL) {
                    edges* sequence = tmp->down;
                    // 이번 순번의 부착간선의 간선에 달린 꼭짓점의 계수를 알아보기
                    vertices* fAnswer = sequence->left;
                    vertices* sAnswer = sequence->right;
                    if (fAnswer->e == rightn) {
                        char correct = sAnswer->e; // 계수 찾음
                        if (correct > leftn) {
                            // 지금 연결하려는 상대 꼭짓점 보다 지금 찾은 계수의 값이 
                            // 더 크면 앞쪽에 붙여야 하므로 부착 간선을 붙여준다
                            if (tmp == p->left) { // 이것이 첫 부착간선의 앞에 가야 한다면
                                newline->next = p->left;
                                p->left = newline;
                                break;
                            }
                            else {
                                incidence* past = p->left;
                                while (1) {
                                    if (past->next == tmp) {
                                        break;
                                    }
                                    past = past->next;
                                }
                                newline->next = tmp;
                                past->next = newline;
                                break;
                            } // 아니라면 사이에 껴준다
                            cnt++; // 등록이 됐다면 올려준다
                        }
                    }
                    else if (sAnswer->e == rightn) {
                        char correct = fAnswer->e; // 계수 찾음
                        if (correct > leftn) {
                            // 지금 연결하려는 상대 꼭짓점 보다 지금 찾은 계수의 값이 
                            // 더 크면 앞쪽에 붙여야 하므로 부착 간선을 붙여준다
                            if (tmp == p->left) { // 이것이 첫 부착간선의 앞에 가야 한다면
                                newline->next = p->left;
                                p->left = newline;
                                break;
                            }
                            else {
                                incidence* past = p->left;
                                while (1) {
                                    if (past->next == tmp) {
                                        break;
                                    }
                                    past = past->next;
                                }
                                newline->next = tmp;
                                past->next = newline;
                                break;
                            } // 아니라면 사이에 껴준다
                            cnt++; // 등록이 됐다면 올려준다
                        }
                    }
                    if (tmp->next == NULL && cnt == 0) {
                        tmp->next = newline;
                        break;
                    }
                    tmp = tmp->next;
                }
            }
            newline->down = newnode; // 마지막으로 부착간선을 간선에 붙인다
        }




        p = p->right;
    }
}

void enqueue(vertices* e) {
    queue* newnode = (queue*)malloc(sizeof(queue));
    newnode->next = NULL;
    newnode->prev = NULL;
    newnode->v = e;
    newnode->next = Q->next;
    if (rear == NULL) {
        Q->next = newnode;
        newnode->prev = Q;
        rear = newnode;
    }
    else {
        Q->next->prev = newnode;
        newnode->prev = Q;
        Q->next = newnode;
    }
}

int isEmpty(queue* q) {
    if (q->next == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

vertices* opposite(vertices* u, incidence* e) {
    edges* e1 = e->down;
    if (e1->left == u) {
        return e1->right;
    }
    else {
        return e1->left;
    }
}

vertices* removeMin() {
    queue* q = Q->next;
    int min = 10000000; // 최소를 무한대
    vertices* tmp = NULL;
    queue* temp = NULL;
    while (q != NULL) {
        vertices* v1 = q->v;
        if (min > v1->d) { // 최소라면 저장해두기
            tmp = v1;
            min = v1->d;
            temp = q;
        }
        q = q->next;
    }
    queue* p = Q;
    while (p != NULL) { // 최소인거 큐에서 삭제
        if (p->next == temp) {
            if (temp->next == NULL) {
                p->next = NULL;
            }
            else {
                p->next = p->next->next;
                p->next->prev = p;
            }
            vertices* t = temp->v;
            free(temp); // 큐 할당해제
            break;
        }
        p = p->next;
    }

    return tmp;
}

void DijkstraShortestPathsSSSTC(int n, char search, char target) { // 의사코드와 동일하게 작성
    vertices* p = head;
    while (p != NULL) { //1
        p->d = 30000;
        p->count = 0; // 경로의 수 초기화
        p = p->right;
    }
    vertices* s = head;
    while (s != NULL) {
        if (s->e == search) {
            break;
        }
        s = s->right;
    }
    vertices* start = s; // oigin 저장
    s->d = 0; //2

    Q = (queue*)malloc(sizeof(queue)); //3 큐 초기화
    Q->next = NULL; Q->prev = NULL;
    Q->v = NULL;
    s = head;
    for (int i = 0; i < n; i++) {
        enqueue(s);
        s = s->right;
    }
    while (!isEmpty(Q)) { // 4
        vertices* u = removeMin();
        incidence* e = u->left;
        while (e != NULL) {
            vertices* z = opposite(u, e);
            edges* tmp = e->down;
            queue* q = Q->next;
            int cnt = 0;
            while (q != NULL) { // 만약 큐에 존재 한다면 cnt++
                vertices* tt = q->v;
                if (tt->e == z->e) {
                    cnt++;
                }
                q = q->next;
            }
            if (u == start) { // 만약 제거된 것이 search라면
                z->count++; // 그에 해당하는 모든 간선의 경로의 수를 1로 만들어 준다
            }
            if (cnt == 1 && tmp->w + u->d < z->d) { // 의사코드와 동일
                z->d = tmp->w + u->d; // 현 최단경로를 계속 저장
            }
            if (tmp->w + u->d == z->d) {
                z->count += u->count; // 최단 거리가 같은 경우 
            } // 원래 지점의 경로의 수를 더 해준다.
            e = e->next;
        }
    }
    vertices* t = head;
    while (t != NULL) {
        if (t->e == target)
            printf("%c, %c : 최단거리 =  %d, 최단경로 수 = %d\n", search, target, t->d, t->count);
        t = t->right;
    }
    queue* L = Q; // 큐 초기화
    while (L != NULL) {
        queue* tmp = L;
        L = L->next;
        free(tmp);
    }
    Q = NULL;
    rear = NULL;
}

int main() {
    int n = 6, m = 9;
    for (char i = 'A'; i <= 'F'; i++) {
        makeVertex(i);
    }

    makeEdges('A', 'B', 8);
    makeEdges('A', 'C', 1);
    makeEdges('A', 'D', 4);
    makeEdges('B', 'C', 7);
    makeEdges('B', 'E', 4);
    makeEdges('C', 'D', 5);
    makeEdges('C', 'E', 3);
    makeEdges('C', 'F', 9);
    makeEdges('D', 'F', 4);
    DijkstraShortestPathsSSSTC(n, 'C', 'A');
    DijkstraShortestPathsSSSTC(n, 'C', 'F');
    DijkstraShortestPathsSSSTC(n, 'F', 'C');
    DijkstraShortestPathsSSSTC(n, 'B', 'D');
    vertices* p = head; // 간선, 지점, 부착간선 모두 해제
    while (p != NULL) {
        vertices* tmpv = p;
        p = p->right;
        incidence* tmpi = tmpv->left;
        while (tmpi != NULL) {
            incidence* tmpii = tmpi;
            tmpi = tmpi->next;
            free(tmpii);
        }
        free(tmpv);
    }
    edges* q = header;
    while (p != NULL) {
        edges* tmpe = q;
        q = q->right;
        free(tmpe);
    }

    return 0;
}