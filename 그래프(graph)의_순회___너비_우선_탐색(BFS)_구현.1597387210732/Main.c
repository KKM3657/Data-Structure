#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 10
#define FALSE 0
#define TRUE 1

// 그래프에 대한 인접 리스트의 노드 구조 정의
typedef struct graphNode {
    int vertex;
    struct graphNode* link;
} graphNode;

typedef struct graphType {
    int n;								// 정점 개수
    graphNode* adjList_H[MAX_VERTEX];	// 정점에 대한 인접 리스트의 헤드 노드 배열
    int visited[MAX_VERTEX];			// 정점에 대한 방문 표시를 위한 배열
} GraphType;

typedef struct _node{
    int data;                           //큐에서 사용될 노드
    struct _node * next;
}Node;

typedef struct _queue{                  //큐를 나타내는 구조체
    Node *front;
    Node *rear;
}Queue;

//큐 초기화
void QueueInit(Queue *q){
    q->front= NULL;
    q->rear= NULL;
}

//큐가 공백인지 확인
int QueueIsEmpty(Queue *q){
    if(q->front == NULL){
        return TRUE;
    } else{
        return FALSE;
    }
}

// 큐에서 정보추가하기
void Enqueue(Queue * q, int data){
    Node * newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if(QueueIsEmpty(q)){
        q->front = newNode;
        q->rear = newNode;
    } else{
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

//큐에서 정보꺼내오기
int Dequeue(Queue * q){
    Node * pNode = q->front;
    int pdata;

    if(QueueIsEmpty(q)){
        printf("오류입니다.\n");
        exit(-1);
    }
    pdata = pNode->data;
    q->front = pNode->next;
    free(pNode);
    if(q->front == NULL){
        q->rear = NULL;
    }
    return  pdata;
}


// 너비 우선 탐색을 위해 초기 공백 그래프를 생성하는 연산
void createGraph(GraphType* g) {
    int v;
    g->n = 0;							// 그래프의 정점 개수를 0으로 초기화
    for (v = 0; v<MAX_VERTEX; v++) {
        g->visited[v] = FALSE;			// 그래프의 정점에 대한 배열 visited를 FALSE로 초기화
        g->adjList_H[v] = NULL;			// 인접 리스트에 대한 헤드 노드 배열을 NULL로 초기화
    }
}

// 그래프 g에 정점 v를 삽입하는 연산
void insertVertex(GraphType* g, int v) {
    if (((g->n) + 1)>MAX_VERTEX) {
        printf("\n 그래프 정점의 개수를 초과하였습니다!");
        return;
    }
    g->n++;
}

//간선 삽입
void insertEdge(GraphType* g, int u, int v) {
    graphNode* node;
    if (u >= g->n || v >= g->n) {
        printf("\n 그래프에 없는 정점입니다!");
        return;
    }
    node = (graphNode *)malloc(sizeof(graphNode));
    node->vertex = v;
    node->link = g->adjList_H[u];
    g->adjList_H[u] = node;
}

// 그래프 g의 각 정점에 대한 인접 리스트를 출력하는 연산
void print_adjList(GraphType* g) {
    int i;
    graphNode* p;
    for (i = 0; i<g->n; i++) {
        printf("\n\t\t정점%c의 인접 리스트", i + 65);
        p = g->adjList_H[i];
        while (p) {
            printf(" -> %c", p->vertex + 65);
            p = p->link;
        }
    }
}

//정점을 한번이라도 방문했는지 확인
int VisitVertex(GraphType * pg, int visitV){
    if(pg->visited[visitV] == 0){
        pg->visited[visitV] = 1;
        printf("%c ", visitV + 65);
        return TRUE;
    }
    return FALSE;
}

//너비 우선 탐색(BFS) 구현
void BFS_adjList(GraphType* g, int startV) {
    Queue queue;
    int visitV = startV;                //시작점 설정
    int nextV;
    graphNode * pNode;

    QueueInit(&queue);
    VisitVertex(g, visitV);             //시작점 방문

    do{
        pNode = g->adjList_H[visitV];                       //인접 리스트의 노드를 가르키는 구조체 포인터
        nextV= g->adjList_H[visitV]->vertex;               //방문할 인접 리스트의 노드

        while(pNode != NULL){                               //해당 인접 리스트 만큼 루프
            if(VisitVertex(g, nextV) == TRUE) {                //해당 인접 리스트를 방문하여 중복방문인지 확인
                Enqueue(&queue, nextV);                        //해당 인접 리스트 노드를 큐에 추가함
            }
            pNode = pNode->link;
            if(pNode== NULL)
                break;
            nextV =pNode->vertex;
        }
            visitV = Dequeue(&queue);                       //다른 인접 리스트의 정점 방문
            for(int i=0; i<g->n; i++){                      //한번도 방문하지 않는 정점이 있으면 큐에 추가
                if(g->visited[i]==0){
                    Enqueue(&queue,visitV);
                }
            }
    }while(!QueueIsEmpty(&queue));
    memset(g->visited, 0, sizeof(int) * MAX_VERTEX);
}

void main() {
    int i;
    GraphType *G9;
    G9 = (GraphType *)malloc(sizeof(GraphType));
    createGraph(G9);

    // 그래프 G9 구성
    for (i = 0; i<7; i++)
        insertVertex(G9, i);
    insertEdge(G9, 0, 2);
    insertEdge(G9, 0, 1);
    insertEdge(G9, 1, 4);
    insertEdge(G9, 1, 3);
    insertEdge(G9, 1, 0);
    insertEdge(G9, 2, 4);
    insertEdge(G9, 2, 0);
    insertEdge(G9, 3, 6);
    insertEdge(G9, 3, 1);
    insertEdge(G9, 4, 6);
    insertEdge(G9, 4, 2);
    insertEdge(G9, 4, 1);
    insertEdge(G9, 5, 6);
    insertEdge(G9, 6, 5);
    insertEdge(G9, 6, 4);
    insertEdge(G9, 6, 3);
    printf("\n G9의 인접 리스트 ");
    print_adjList(G9);

    printf("\n\n///////////////\n\n너비 우선 탐색 >> ");
    BFS_adjList(G9, 0);      // 0번 정점인 정점 A에서 너비 우선 탐색 시작

}