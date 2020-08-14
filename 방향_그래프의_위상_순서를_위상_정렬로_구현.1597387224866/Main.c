#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define MAX_VERTEX 10
#define MAX_VERTICES 100

// 그래프에 대한 인접 리스트의 노드 구조 정의
typedef struct _graphNode {
    int vertex;
    int num;
    struct _graphNode* link;
} graphNode;

// 간선을 나타내는 구조체
typedef struct _Edge {
    int start;
    int end;
}Edge;

typedef struct _graphType {
    int numV;                           // 정점 개수
    int numE;
    graphNode* adjList_H[MAX_VERTEX];	// 정점에 대한 인접 리스트의 헤드 노드 배열
    int indegree[MAX_VERTEX];			// 정점에 대한 방문 표시를 위한 배열
    Edge edges[2 * MAX_VERTICES];
} graphType;


//초기 공백 그래프를 생성하는 연산
void createGraph(graphType* g) {
    int v;
    g->numV = 0;						// 그래프의 정점 개수를 0으로 초기화
    g->numE = 0;
    for (v = 0; v<MAX_VERTEX; v++) {
        g->indegree[v] = 0;			// 그래프의 정점에 대한 배열 indegree 초기화
        g->adjList_H[v] = NULL;			// 인접 리스트에 대한 헤드 노드 배열을 NULL로 초기화
    }
    for (int i = 0; i < 2 * MAX_VERTICES; i++) {
        g->edges[i].start = 0;          //edge 배열 초기화
        g->edges[i].end = 0;
    }
}

// 그래프 g에 정점 v를 삽입하는 연산
void insertVertex(graphType* g, int v) {
    if (((g->numV) + 1)>MAX_VERTEX) {
        printf("\n 그래프 정점의 개수를 초과하였습니다!");
        return;
    }
    g->numV++;
}

// 그래프 g에 간선 (u, v)를 삽입하는 연산
void insertEdge(graphType* g, int u, int v) {
    graphNode* node1;

    if (u >= g->numV || v >= g->numV) {
        printf("\n 그래프에 없는 정점입니다!");
        return;
    }
    //edges 배열에 간선 저장
    g->edges[g->numE].start = u;
    g->edges[g->numE].end = v;
    g->indegree[v]++;
    g->numE += 1;

    //인접연결리스트 구현
    node1 = (graphNode*)malloc(sizeof(graphNode));
    node1->vertex = v;
    node1->link = g->adjList_H[u];
    g->adjList_H[u] = node1;

}

// 그래프 g의 각 정점에 대한 인접 리스트를 출력하는 연산
void print_adjList(graphType* g) {
    int i;
    graphNode* p;
    for (i = 0; i<=g->numV; i++) {
        printf("\n\t\t정점%d의 인접 리스트", i);
        p = g->adjList_H[i];
        while (p) {
            printf(" -> %d", p->vertex);
            p = p->link;
        }
    }
}

int stak[MAX_VERTEX];           //스택을 배열로 생성
int res[MAX_VERTEX];            //결과값을 저장하기 위한 배열
int res_idx =0 ;                //result 배열 인덱스 초기화

void topological_sort(int cur, graphType *g) {

    // 현재 방문하는 정점의 indegree 1 감소=
    if(g->indegree[cur] != 0){
        g->indegree[cur] -= 1;
    }
    // indegree[cur] == 0이면 res[res_idx]에 추가, return;
    if(g->indegree[cur] == 0){
        res[res_idx]= cur;
        res_idx++;
    }
    else{
        return;
    }
    graphNode *next = g->adjList_H[cur];

    //다음 인접리스트의 indegree가 있을경우
    while(next != NULL &&  g->indegree[next->vertex] != 0){
        topological_sort(next->vertex, g);
        next = next->link;
    }
}

int main() {
    int num_nodes = 9, num_edges = 10;
    int i;
    graphType *g;
    g = (graphType *)malloc(sizeof(graphType));
    createGraph(g);

    // 그래프 g 구성
    for (i = 0; i<num_nodes; i++)
        insertVertex(g, i);
    insertEdge(g, 0, 1);
    insertEdge(g, 0, 2);
    insertEdge(g, 1, 3);
    insertEdge(g, 1, 4);
    insertEdge(g, 2, 4);
    insertEdge(g, 2, 5);
    insertEdge(g, 3, 6);
    insertEdge(g, 4, 7);
    insertEdge(g, 6, 7);
    insertEdge(g, 6, 8);

    printf("\n G7의 인접 리스트 ");
    print_adjList(g);

    int top_idx = 0;
    for(int i=0;i<num_nodes;++i) {          //indegree가 0인 것을 우선적으로 스택 배열에 저장
        if(g->indegree[i] == 0) {
            stak[top_idx] = i;
            top_idx++;
        }
    }

    for(int i=top_idx;i>=0;--i) {           //위상정렬 시작
        topological_sort(stak[top_idx], g);				//스택을 이용한 위상정렬
    }

    printf("\n");
    printf("\n");

    printf("위상정렬: ");
    for(int i =0; i<num_nodes; i++){
        printf("%d ", res[i]);
    }

    free(g);
    return 0;
}
