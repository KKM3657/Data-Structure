#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define QUE_LEN 100

typedef int Data;
typedef struct _cQuere{
    int front;
    int rear;
    Data queArr[QUE_LEN];
}CQueue;
typedef CQueue Queue;

void QueueInit(Queue *pQ){
    pQ->front =0;
    pQ->rear =0;
}

int QIsEmpty(Queue *pQ){
    if(pQ->front == pQ->rear)
        return  TRUE;
    else
        return FALSE;
}

int NextPosIdx(int pos){
    if(pos == QUE_LEN-1)
        return 0;
    else
        return pos+1;
}

void Enqueue(Queue *pQ, Data data){
    if(NextPosIdx(pQ->rear) == pQ->front){
        printf("배열이 꽉찼습니다.");
        return;
    }
    pQ->rear = NextPosIdx(pQ->rear);
    pQ->queArr[pQ->rear]= data;
}

Data Dequeue(Queue *pQ){
    int rdata;
    if(QIsEmpty(pQ)){
        exit(-1);
    }
    pQ->front= NextPosIdx(pQ->front);
    rdata = pQ->queArr[pQ->front];
    return rdata;
}

Data Qpeek(Queue *pQ){
    if(QIsEmpty(pQ)){
        exit(-1);
    }
    return pQ->queArr[NextPosIdx(pQ->front)];
}

int main(void){
    Queue q;
    QueueInit(&q);

    Enqueue(&q,1);  Enqueue(&q,2);
    Enqueue(&q,3);  Enqueue(&q,4);
    Enqueue(&q,5);

    while(!QIsEmpty(&q)){
        printf("%d ", Dequeue(&q));
    }
    return 0;
}
