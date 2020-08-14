#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//구조체 ListNode 생성
typedef struct ListNodeType{
    char data[3];
    struct ListNodeType *link;
} ListNode;

//구조체 ListType 생성 (꼬리부분)
typedef struct ListType{
    ListNode *head;
    ListNode *tail;
} ListType;

//공백리스트 생성
ListType * createList(void) {
    ListType * pList;
    pList = (ListType *)malloc(sizeof(ListType));       //동적할당
    pList->head = NULL;
    pList->tail = NULL;
    return pList;
}

void insertFrontNode(ListType* pList, char* c) {
    ListNode* newNode;
    newNode = (ListNode*)malloc(sizeof(ListNode));	// 삽입할 새 노드 할당
    strcpy(newNode->data, c);						// 새 노드의 데이터 필드에 a 저장
    newNode->link = pList->head;
    pList->head = newNode;
}
//마지막 노드에 자료 추가
void listEndAdd(ListType* pList, char *c){
    ListNode* pNode;
    ListNode* newNode;
    newNode = (ListNode *)malloc(sizeof(ListNode));
    strcpy(newNode->data,c);
    newNode->link= NULL;                                   //pList->head; 하면 원형 리스트 완성
    //무한루프가 돌게 된다.

    if(pList->head == NULL){                               //공백리스트인 경우
        pList->head = newNode;                             //새로운 노드를 꼬리부분에 저장
    }
    else{                                                  //공백리스트가 아닌경우
        pNode= pList->head;
        while(pNode->link != pList->tail){
            pNode=pNode->link;
        }
        pNode->link = newNode;
    }
}


//n번째 노드에 자료 추가
void listAdd(ListType* pList, char *c, int num){
    ListNode* newNode;
    ListNode* pNode;
    int count =0;                                           //꼬리 다음부터 노드 번호를 셈
    newNode = (ListNode *)malloc(sizeof(ListNode));
    strcpy(newNode->data,c);

    if(pList == NULL){                                      //공백리스트 일때
        pList->head = newNode;
        newNode->link=NULL;
    }
    else if(num == 1){                                      //첫번째 노드에 삽입할때
        newNode->link= pList->head;                         //꼬리에 새로운 노드를 연결함
        pList->head = newNode;
    }
    else {                                                  //n번째 노드에 삽입할때
        pNode=pList->head;
        while (pNode != pList->tail) {
            count++;
            if (num - 1 == count) {                         //n번째 노드와 n-1번째 노드사이에 노드 삽입
                (newNode->link) = (pNode->link);
                pNode->link = newNode;
            }
            pNode = pNode->link;
        }
    }

}


//노드 값 탐색
void findNodeValue(ListType* pList, char* c){
    ListNode* pNode;
    int answer =0;
    int count=0;
    pNode= pList->head;
    while(pNode != NULL){                                   //원형리스트 한 사이클로 계산
        count++;                                            //노드 개수
        if(strcmp(c,pNode->data) == 0) {                    //노드의 원소값을 탐색 조건문
            printf("%d번째 노드에 있습니다.\n",count);
            answer++;
        }
        pNode= pNode->link;                                 //다음 노드로 이동
    }
    if( answer == 0){
        printf("없습니다.\n");
    }
    else{
        printf("%d개 있습니다.\n",answer);                   //노드 개수 출력
    }
    printf("\n");
}


//탐색한 노드 원소 출력
ListNode* printNodeValue(ListType* pList, char* c){
    ListNode* pNode;
    int count=0;
    pNode= pList->head;
    while(pNode != pList->tail){                                   //원형리스트 한 사이클
        if(strcmp(c,pNode->data) == 0) {                           //노드 원소값 탐색 조건문
            return pNode;                                          //노드 원소값 반환
        }
        pNode= pNode->link;                                        //다음 노드로 이동
    }
    return NULL;                                                   //탐색한 노드 원소가 없을경우
}

//노드 원소 출력
void printValue(ListNode *pNode){
    printf("pNode = (%s)\n\n",pNode->data);

}


//노드 삭제
void listEraseValue(ListType* pList, ListNode *pNode){
    ListNode* prev;
    if(pList->head == NULL){                                        //공백리스트 일경우
        return;
    }
    if(pNode==NULL){                                                //삭제할 원소가 없을 경우
        printf("삭제할 값이 없습니다.\n");
    }
    else if(pList->head ==pNode) {                                  //노드가 1개일 경우
        pList->head=pNode->link;
        free(pNode);
    }
    else if((pList->head)->link == NULL){                           //1번째 노드 삭제
        free(pList->head);
        pList->head= NULL;
        return;
    }
    else {                                                          //탐색한 노드삭제
        prev = pList->head;
        while (prev->link != pNode) {
            prev = prev->link;
        }
        prev->link = pNode->link;                                   // 삭제할 노드 pNode의 선행자 노드와 다음 노드를 연결
        free(pNode);
    }
}
//노드의 개수 출력
void printNodeNum(ListType* pList){
    ListNode* pNode;
    int num =0;
    pNode= pList->head;
    if(pNode == NULL){                                             //공백리스트 일경우
        printf("노드의 개수는 0입니다.\n");
    } else{                                                       //연결된 노드를 거쳐가면서 개수 증가
        while(pNode != pList->tail){
            num++;
            pNode= pNode->link;                                    //다음노드로 이동
        }
        printf("노드의 개수는 %d입니다.\n",num);
    }

    printf("\n");
}
//노드의 원소 출력
void printList(ListType* pList){
    ListNode* pNode;
    printf("pList = (");
    pNode = pList->head;                                           //꼬리노드로 이용하여 원형리스트 접근
    while(pNode != pList->tail){                                          //원형 리스트 1사이클 출력
        printf("%s",pNode->data);
        pNode = (pNode->link);                                     //다음 노드로 이동
        if(pNode != pList->tail){                                         //노드가 끝날때마다 ","출력
            printf(",");
        }
    }
    printf(")\n");
}

int main(void){
    ListType * pList;
    ListNode * pNode;

    pList= createList();
    printList(pList);
    printNodeNum(pList);

    printf("리스트에 '료' 추가\n");
    insertFrontNode(pList,"료");
    printList(pList);
    printNodeNum(pList);

    printf("리스트에 '구' 추가\n");
    listEndAdd(pList,"구");
    printList(pList);
    printNodeNum(pList);

    printf("리스트 맨 앞에 '자' 추가\n");
    listAdd(pList,"자",1);
    printList(pList);
    printNodeNum(pList);

    printf("3번째 리스트에 '의' 추가\n");
    listAdd(pList,"의",3);
    printList(pList);
    printNodeNum(pList);

    printf("리스트에서 '의' 탐색\n");
    findNodeValue(pList,"의");

    printf("1번째 리스트에 '한' 추가\n");
    listAdd(pList,"한",1);
    printList(pList);
    printNodeNum(pList);

    printf("4번째 리스트 원소 '의' 제거\n");
    pNode = printNodeValue(pList,"의");
    listEraseValue(pList,pNode);
    printList(pList);
    printNodeNum(pList);

    printf("리스트에 '조' 추가\n");
    listEndAdd(pList,"조");
    printList(pList);
    printNodeNum(pList);

    printf("1번째 리스트 원소 '한' 반환\n");
    pNode = printNodeValue(pList,"한");
    printValue(pNode);

    printf("1번째 리스트 원소 '한' 제거\n");
    pNode = printNodeValue(pList,"한");
    listEraseValue(pList,pNode);
    printList(pList);
    printNodeNum(pList);

    printf("메모리 제거\n");
    free(pList);
    free(pNode);

    return 0;
}