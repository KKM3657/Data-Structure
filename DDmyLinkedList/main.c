#include <stdio.h>
#include <stdlib.h>


#define TRUE 1
#define FALSE 0

typedef  int Data;

typedef struct _Node{
    int data;
    struct _Node *next;
    struct _Node *prev;
}Node;

typedef struct _List{
    Node *head;
    Node *tail;
    Node *cur;
    int numOfData;
}DDmyLinkedList;

typedef DDmyLinkedList List;

void ListInit(List *plist){
    plist->head = (Node*)malloc(sizeof(Node));
    plist->tail = (Node*)malloc(sizeof(Node));

    plist->head->next = plist->tail;
    plist->head->prev = NULL;

    plist->tail->prev = plist->head;
    plist->tail->next = NULL;

    plist->numOfData = 0;
}

void LInsert(List *plist, Data data){
    Node * newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;

    newNode->prev = plist->tail->prev;
    plist->tail->prev->next = newNode;

    newNode->next = plist->tail;
    plist->tail->prev= newNode;

    plist->numOfData++;
}

int LFirst(List *plist, Data *pdata){
    if(plist->head->next == plist->tail){
        return FALSE;
    }

    plist->cur = plist->head->next;
    *pdata = plist->cur->data;
    return  TRUE;
}

int LNext(List *plist, Data *pdata){
    if(plist->cur->next == plist->tail){
        return  FALSE;
    }

    plist->cur= plist->cur->next;
    *pdata = plist->cur->data;
    return TRUE;
}
int LPrevious(List *plist , Data *pdata){
    if(plist->cur->prev == plist->head){
        return FALSE;
    }

    plist->cur = plist->cur->prev;
    *pdata = plist->cur->data;
    return TRUE;
}

Data LRemove(List *plist){
    Node * rpos = plist->cur;
    Data remv =rpos->data;

    rpos->next->prev = rpos->prev;
    rpos->prev->next = rpos->next;

    plist->cur = plist->cur->prev;
    free(rpos);
    plist->numOfData--;
    return remv;
}
int main(void){
    //양방향 연결 리스트의 생성 및 초기화
    List list;
    int data;
    ListInit(&list);

    //8개의 데이터 저장
    LInsert(&list, 1); LInsert(&list, 2);
    LInsert(&list, 3); LInsert(&list, 4);
    LInsert(&list, 5); LInsert(&list, 6);
    LInsert(&list, 7); LInsert(&list, 8);

    //저장된 데이터 조회
    if(LFirst(&list, &data)){
        printf("%d ",data);

        //오른쪽 노드로 이동하며 데이터 조회
        while(LNext(&list, &data))
            printf("%d ",data);

        while(LPrevious(&list, &data))
            printf("%d ",data);

        printf("\n\n");
    }

    //2의 배수 전부 삭제
    if(LFirst(&list, &data)){
        if(data %2 == 0){
            LRemove(&list);
        }
        while (LNext(&list,&data)){
            if(data %2 == 0){
                LRemove(&list);
            }
        }
    }

    //저장된 데이터 조회
    if(LFirst(&list, &data)){
        printf("%d ",data);

        //오른쪽 노드로 이동하며 데이터 조회
        while(LNext(&list, &data))
            printf("%d ",data);

        printf("\n\n");
    }

    return 0;
}