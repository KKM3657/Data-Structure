#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 3

typedef struct __Node{
    char data[LEN];
    struct __Node * next;
}ListNode;

typedef struct __List{
    ListNode * head;
    int nodeNum;
}ListHead;

ListHead * ListInit(ListHead * pList){
    pList = (ListHead *)malloc(sizeof(ListHead));
    pList->head = NULL;
    pList->nodeNum = 0;
    return pList;
}

void printList(ListHead * pList){
    ListNode * pNode;
    pNode = pList->head;
    printf("List = { ");
    while(pNode != NULL){
        printf("%s",pNode->data);
        pNode= pNode->next;
        if(pNode != NULL){
            printf(", ");
        }
    }
    printf(" }\n\n");
}

void ListNodeAdd(ListHead * pList, char *c, int num){
    ListNode * temp;
    ListNode * newNode= (ListNode *)malloc(sizeof(ListNode));
    strcpy(newNode->data,c);
    newNode->next = NULL;

    if(pList->head == NULL){
        pList->head = newNode;
        (pList->nodeNum)++;
    }
    else if(num ==1){
        newNode->next= pList->head;
        pList->head = newNode;
        (pList->nodeNum)++;
    }
    else {
        temp = pList->head;
        while(temp->next != NULL){
            temp =temp->next;
        }
        temp->next = newNode;
        (pList->nodeNum)++;
    }
}

void ListmidAdd(ListHead * pList, char *c, ListNode * prev){
    ListNode * pNode;
    ListNode * newNode =(ListNode *)malloc(sizeof(ListNode));
    strcpy(newNode->data, c);
    newNode->next = NULL;
    pNode= pList->head;
    while(pNode !=prev){
        pNode= pNode->next;
    }
    newNode->next= pNode->next;
    pNode->next= newNode;
}

ListNode * ListFind(ListHead *pList, char *c){
    ListNode *pNode;
    pNode = pList->head;
    while(pNode != NULL) {
        if(strcmp(pNode->data,c)==0){
            printf("탐색 성공\n\n");
            return pNode;
        }
        pNode= pNode->next;
    }
    printf("탐색 실패\n\n");
    return NULL;
}

void ListNodeRemove(ListHead *pList, ListNode *prev){
    ListNode * pNode;
    pNode= pList->head;
    if (prev == NULL) return;
    else {
        while(pNode->next != prev){
            pNode= pNode->next;
        }
        pNode->next = prev->next;
        free(prev);
    }
}

int main(void){
    ListHead * list;
    ListNode * node;

    printf("공백리스트 추가\n");
    list= ListInit(list);
    printList(list);

    printf("\"자\"노드 추가\n");
    ListNodeAdd(list,"자",1);
    printList(list);

    printf("\"료\"노드 추가\n");
    ListNodeAdd(list,"료",2);
    printList(list);

    printf("\"한\"노드를 맨 앞에 추가\n");
    ListNodeAdd(list,"한",1);
    printList(list);

    printf("\"구\"노드 추가\n");
    ListNodeAdd(list,"구",2);
    printList(list);

    printf("\"료\"노드 탐색\n");
    node = ListFind(list,"료");

    printf("\"의\"노드를 \"료\"노드 뒤에 추가\n");
    ListmidAdd(list,"의",node);
    printList(list);

    printf("\"구\"노드 탐색\n");
    node = ListFind(list,"구");

    printf("\"조\"노드를 \"구\"노드 뒤에 추가\n");
    ListmidAdd(list,"조",node);
    printList(list);

    printf("\"한\"노드 탐색 후 제거\n");
    node = ListFind(list,"한");
    ListNodeRemove(list, node);
    printList(list);

    return 0;
}