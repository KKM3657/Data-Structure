#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define MAX_VERTEX 10
#define MAX_VERTICES 100
#define INF 1000
#define FALSE 0
#define TRUE 1

// 그래프에 대한 인접 리스트의 노드 구조 정의
typedef struct _graphNode {
    int vertex;
    int weight;
    struct _graphNode* link;
} graphNode;

// 간선을 나타내는 구조체
typedef struct _Edge {
    int start;
    int end;
    int weight;
}Edge;

typedef struct _graphType {
    int numV;                           // 정점 개수
    int numE;
    graphNode* adjList_H[MAX_VERTEX];	// 정점에 대한 인접 리스트의 헤드 노드 배열
    int visited[MAX_VERTEX];			// 정점에 대한 방문 표시를 위한 배열
    Edge edges[2 * MAX_VERTICES];
} graphType;

typedef struct stackNode {
    int data;
    struct stackNode *link;
} stackNode;

typedef struct _stack {
    struct stackNode * front;
} Stack;

// 스택 초기화
void StackInit(Stack * pStack){
    pStack->front = NULL;
}

// 스택이 공백인지 확인하는 연산
int isEmpty(Stack * pStack) {
    if (pStack->front == NULL) return 1;
    else return 0;
}

// 스택에 데이터 추가
void push(Stack * pStack, int item) {
    stackNode* temp = (stackNode *)malloc(sizeof(stackNode));
    temp->data = item;
    temp->link = pStack->front;
    pStack->front = temp;
}

// 스택에 데이터 꺼내기
int pop(Stack * pStack) {
    int item;
    stackNode* temp = pStack->front;

    if (isEmpty(pStack)) {
        printf("\n\n Stack is empty !\n");
        return 0;
    }
    else {
        item = temp->data;
        pStack->front = temp->link;
        free(temp);
        return item;
    }
}

// 깊이 우선 탐색을 위해 초기 공백 그래프를 생성하는 연산
void createGraph(graphType* g) {
    int v;
    g->numV = 0;						// 그래프의 정점 개수를 0으로 초기화
    g->numE = 0;
    for (v = 0; v<MAX_VERTEX; v++) {
        g->visited[v] = FALSE;			// 그래프의 정점에 대한 배열 visited를 FALSE로 초기화
        g->adjList_H[v] = NULL;			// 인접 리스트에 대한 헤드 노드 배열을 NULL로 초기화
    }
    for (int i = 0; i < 2 * MAX_VERTICES; i++) {
        g->edges[i].start = 0;          //edge 배열 초기화
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
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
void insertEdge(graphType* g, int u, int v, int w) {
    graphNode* node1;
    graphNode* node2;

    if (u >= g->numV || v >= g->numV) {
        printf("\n 그래프에 없는 정점입니다!");
        return;
    }
    //edges 배열에 간선 저장
    g->edges[g->numE].start = u;
    g->edges[g->numE].end = v;
    g->edges[g->numE].weight = w;
    g->numE += 1;

    //인접연결리스트 구현
    node1 = (graphNode*)malloc(sizeof(graphNode));
    node1->vertex = v;
    node1->weight = w;
    node1->link = g->adjList_H[u];
    g->adjList_H[u] = node1;

    node2 = (graphNode*)malloc(sizeof(graphNode));
    node2->vertex = u;
    node2->weight = w;
    node2->link = g->adjList_H[v];
    g->adjList_H[v] = node2;

}

//정렬된 배열 출력
void print_sort(graphType* g, int n)
{
    for (int i = 0; i<n; i++) {
        printf("(%d,", g->edges[i].start);
        printf("%d,", g->edges[i].end);
        printf("%d) ", g->edges[i].weight);
    }
    printf("\n\n");
}

//정렬을 위한 compare함수
int compare(const void* a, const void* b)
{
    Edge* x = ( Edge*)a;
    Edge* y = ( Edge*)b;
    return (y->weight - x->weight);      // 내림 차순
}

// 그래프 g의 각 정점에 대한 인접 리스트를 출력하는 연산
void print_adjList(graphType* g) {
    int i;
    graphNode* p;
    for (i = 0; i<g->numV; i++) {
        printf("\n\t\t정점%c의 인접 리스트", i + 65);
        p = g->adjList_H[i];
        while (p) {
            printf(" -> %c", p->vertex + 65);
            p = p->link;
        }
    }
}

//방문기록 저장후 중복방문인지 확인
int VisitVertex(graphType * g, int visitV){
    if(g->visited[visitV] == 0){
        g->visited[visitV] = 1;
        return TRUE;
    }
    return FALSE;
}

// 그래프 g에서 깊이 우선 탐색을 이용하여 정점 v1과 v2가 연결되어 있는지 확인
int IsConnVertex(graphType* g, int v1, int v2) {
    Stack stack;                    //스택 설정

    graphNode* pNode;
    int visitV = v1;                //시작점 설정
    int nextV;
    StackInit(&stack);
    push(&stack,v1);				// 깊이 우선 탐색을 시작하는 정점 v를 스택에 push
    VisitVertex(g, visitV);	        // 정점 v를 방문했으므로 해당 배열 값을 TRUE로 설정

    //만약 인접리스트 간선 삭제후 공백이면 넘어감
    if(g->adjList_H[visitV] == NULL){
        return FALSE;
    }

    // 스택이 공백이 아닌 동안 깊이 우선 탐색 반복
    do{
        pNode = g->adjList_H[visitV];                       //인접 리스트의 노드를 가르키는 구조체 포인터
        nextV= g->adjList_H[visitV]->vertex;
        // 인접 정점이 있는 동안 수행
        while (pNode != NULL) {
            if(nextV == v2){                                //깊이 우선 탐색중 정점v2를 지나가면 참 출력
                memset(g->visited, 0, sizeof(int) * MAX_VERTEX);
                return TRUE;
            }
            if (VisitVertex(g, nextV) == TRUE) {             //해당 인접 리스트를 방문하여 중복방문인지 확인
                push(&stack, nextV);                        //해당 인접 리스트 노드를 스택에 추가함
            }
            pNode = pNode->link;
            if (pNode == NULL)
                break;
            nextV = pNode->vertex;
        }
        visitV = pop(&stack);
    }while (!isEmpty(&stack));
    memset(g->visited, 0, sizeof(int) * MAX_VERTEX);        //방문기록 초기화
    return FALSE;                                           //깊이 우선 탐색후 연결되어있지 않아 거짓 출력
}

//인접리스트에서 간선 제거
void RemoveWayEdge(graphType *g, int u, int v){

    graphNode * pNode = g->adjList_H[u];
    graphNode * before = NULL;
    while(pNode != NULL){                           //해당 간선을 찾을때 까지 반복
        if(pNode->vertex == v) {                    //가중치를 이용해서 해당 간선을 찾음
            if(pNode == g->adjList_H[u]){           //인접리스트에서 첫번째 노드 삭제
                g->adjList_H[u]= pNode->link;

                free(pNode);
                return;
            }else{                                  //인접리스트에서 첫번째 이후 노드 삭제
                before->link = pNode->link;

                free(pNode);
                return;
            }
        }
        before= pNode;
        pNode= pNode->link;
    }
}

//해당 간선 제거
void RemoveEdge(graphType *g, int u, int v){
    RemoveWayEdge(g, u, v);
    RemoveWayEdge(g, v, u);
    (g->numE)--;
}

//해당 간선 복구
void RecoverEdge(graphType *g, int u, int v, int w){
    graphNode* node;
    node = (graphNode *)malloc(sizeof(graphNode));
    node->vertex = v;
    node->weight = w;
    node->link = g->adjList_H[u];
    g->adjList_H[u] = node;
    (g->numE)++;
}

//크루스칼 알고리즘 1 구현
Edge * ConKruskalMst(graphType *g, Edge * recvEdge){
    Edge edge;
    int eidx = 0;
    int i =0;

    qsort(g->edges, g->numE, sizeof(Edge), compare);            //가중치와 간선 정보를 저장된 배열을 내림차순으로 정렬
    printf("\n정렬: ");
    print_sort(g,g->numE);

    //최소비용 신장트리 구현
    while(g->numE+1 > g->numV){                                 //그래프 G에 간선이 N-1개 남을때 까지 반복
        edge = g->edges[i++];                                   //가중치와 간선 정보가 저장된 배열을 불러오기
        RemoveEdge(g,edge.start, edge.end);                     //가중치가 가장 높은 간선 제거
        printf("(%d, %d, %d)삭제\n",edge.start, edge.end, edge.weight);

        if(!IsConnVertex(g,edge.start,edge.end))  {              //간선 제거후 깊이 우선 탐색을 이용하여
                                                                 //각 정점들이 연결되어 있는지 확인
            RecoverEdge(g, edge.start, edge.end, edge.weight);      //연결되어 있지 않으면 간선 복원
            printf("(%d, %d, %d)복원\n",edge.start, edge.end, edge.weight);
            recvEdge[eidx++] = edge;                            //복원한 간선 정보를 배열에 저장
        }

        for(int j = 0; j<eidx; j++){                            //복원한 간선 정보를 내림차순으로 정렬
            qsort(recvEdge, j, sizeof(Edge), compare);
        }
    }
    printf("최소 비용 신장트리 완료");
    return recvEdge;
}

int main() {
    int i;
    Edge recvEdge[10];
    memset(recvEdge, 0, sizeof(Edge)*10);
    graphType *g;
    g = (graphType *)malloc(sizeof(graphType));
    createGraph(g);

    // 그래프 g 구성
    for (i = 0; i<7; i++)
        insertVertex(g, i);
    insertEdge(g, 0, 1, 3);
    insertEdge(g, 0, 2, 17);
    insertEdge(g, 0, 3, 6);
    insertEdge(g, 1, 3, 5);
    insertEdge(g, 1, 6, 12);
    insertEdge(g, 2, 4, 10);
    insertEdge(g, 2, 5, 8);
    insertEdge(g, 3, 4, 9);
    insertEdge(g, 4, 5, 4);
    insertEdge(g, 4, 6, 2);
    insertEdge(g, 5, 6, 14);

    printf("\n G7의 인접 리스트 ");
    print_adjList(g);

    printf("\n\n///////////////\n\n크루스칼 최소 신장 트리 알고리즘 -1");
    ConKruskalMst(g, recvEdge);
    printf("\n\n///////////////\n\n결과 :\n");
    for(i= 0 ; i<10; i++){
        if(recvEdge[i].weight == 0){
            break;
        }
        printf("간선(%d, %d) %d 선택\n",recvEdge[i].start, recvEdge[i].end, recvEdge[i].weight);
    }
    for(i=g->numE+1; i<11; i++){
        printf("간선(%d, %d) %d 선택\n",g->edges[i].start, g->edges[i].end, g->edges[i].weight);
    }
    free(g);
    return 0;
}
