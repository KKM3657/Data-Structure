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
    int numofData;
}CList;

void ListInit(CList *plist){
    plist->tail = NULL;
    plist->cur = NULL;
    plist->before=NULL;
    plist->numofData =0;
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
    (plist->numofData)++;
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
    (plist->numofData)++;
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

    (plist->numofData)--;
    return rdata;
}

int LCount(CList *plist){
    return  plist->numofData;
}