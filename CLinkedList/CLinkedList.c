#include <stdio.h>
#include <stdlib.h>

typedef int Data;

typedef struct _node{
    Data data;
    struct _node * next;
}Node;

typedef struct _CList{
    Node * tail;
    Node * cur;
    Node * before;
    int numOfData;
}CList;

void ListInit(CList *plist){
    plist->tail = NULL;
    plist->cur = NULL;
    plist->before=NULL;
    plist->numOfData =0;
}

void ListInsertFront(CList *plist, Data data){
    Node * newNode = (Node*)malloc(sizeof(Node));
    newNode->data= data;

    if(plist->tail == NULL){
        plist->tail = newNode;
        newNode->next= newNode;
        return;
    }
    else{
        newNode->next=  plist->tail->next;
        plist->tail->next =newNode;
    }
    (plist->numOfData)++;
}

void LInsert(CList * plist, Data data){
    Node * newNode =(Node*)malloc(sizeof(Node));
    newNode->data = data;

    if(plist->tail == NULL){
        plist->tail = newNode;
        newNode->next = newNode;
    }
    else{
        newNode->next = plist->tail->next;
        plist->tail->next = newNode;
        plist->tail= newNode;
    }
    (plist->numOfData)++;
}

int LFirst(CList *plist, Data *pdata){
    if(plist->tail == NULL){
        return 0;
    }
    plist-> before = plist->tail;
    plist->cur = plist->tail->next;

    *pdata= plist->cur->data;
    return  1;
}

int LNext(CList *plist, Data * pdata){
    if(plist->tail == NULL){
        return  0;
    }
    plist->before = plist->cur;
    plist->cur = plist->cur->next;

    *pdata = plist->cur->data;
    return 1;
}

Data LRemove(CList *plist){
    Node * rpos = plist->cur;
    Data rdata = rpos->data;

    if(rpos == plist->tail){
        if(plist->tail == plist->tail->next){
            plist->tail = NULL;
        }
        else{
            plist->tail= plist->before;
        }
    }
    plist->before->next = rpos->next;
    plist->cur= plist->before;
    free(rpos);

    (plist->numOfData)--;
    return rdata;
}

int LCount(CList *plist){
    return  plist->numOfData;
}

int main(void) {
    //원형 연결 리스트의 생성 및 초기화//
    CList list;
    int data, i, nodeNum;
    ListInit(&list);

    //리스트에 5개의 데이터를 저장//
    LInsert(&list, 3);
    LInsert(&list, 4);
    LInsert(&list, 5);
    ListInsertFront(&list, 2);
    ListInsertFront(&list, 1);

    //리스트에 저장된 데이터를 연속 3회 출력//
    if (LFirst(&list, &data)) {
        printf("%d ", data);

        for (i = 0; i < LCount(&list) * 3 - 1; i++) {
            if (LNext(&list, &data))
                printf("%d ", data);
        }
    }
    printf("\n");

    //2의 배수를 찾아서 모두 삭제//
    nodeNum = LCount(&list);

    if (nodeNum != 0) {
        LFirst(&list, &data);
        if (data % 2 == 0) {
            LRemove(&list);
        }

        for (i = 0; i < nodeNum - 1; i++) {
            LNext(&list, &data);
            if (data % 2 == 0) {
                LRemove(&list);
            }
        }
    }

    // 전체 데이터 1회 출력
    if (LFirst(&list, &data)) {
        printf("%d ", data);

        for (i = 0; i < LCount(&list) - 1; i++) {
            if (LNext(&list, &data))
                printf("%d ", data);
        }
    }
    return 0;
}
