#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 3

typedef struct __Node{                   //노드 구조체
    char data[LEN];
    struct __Node * next;
}ListNode;

typedef struct __List{                   //원형연결 리스트 구조체
    ListNode * head;
    int nodeNum;
}ListHead;

//공백원형 리스트 생성
ListHead * ListInit(ListHead * pList){
    pList = (ListHead *)malloc(sizeof(ListHead));
    pList->head = NULL;                             //리스트 초기화
    pList->nodeNum = 0;
    return pList;
}

//원형리스트 출력
void printList(ListHead * pList){
    ListNode * pNode;
    pNode = pList->head;
    if(pList->head == NULL){                 //공백리스트 일때
        printf("없음\n");
        return;
    }
    printf("List = { ");
    do{
        printf("%s",pNode->data);
        pNode= pNode->next;
        if(pNode != pList->head){
            printf(", ");
        }
    }while(pNode != pList->head);             //헤드 노드가 나올때 까지 반복
    printf(" }\n");
}
//노드 갯수 출력
void ListNodeNum(ListHead * pList){
    printf("노드의 갯수는 %d개 입니다.\n\n" ,pList->nodeNum);
}

//데이터를 받아 리스트에 추가
void ListNodeAdd(ListHead * pList, char *c, int num){
    ListNode * temp;
    ListNode * prev;
    ListNode * newNode= (ListNode *)malloc(sizeof(ListNode));           //노드 생성
    strcpy(newNode->data,c);
    newNode->next = NULL;

    if(pList->head == NULL){            //공백리스트일경우
        pList->head = newNode;
        newNode->next=pList->head;
        (pList->nodeNum)++;
    }
    else if(num ==1){                   //1번에 넣을경우
        prev = pList->head;             //1번 노드를 가르키는 포인트 구조체
        newNode->next= pList->head;     //마지막 노드를 생성한 노드에 연결
        pList->head = newNode;          //헤드 노드가 생성한 노드를 가르킴
        temp = pList->head;             //수정된 원형리스트의 1번 노드를 가르킴
        do{
            temp=temp->next;            //다음 노드로 이동
        }while(temp->next != prev);     //수정된 원형 리스트의 한 루프
        temp->next=pList->head;         //마지막노드를 1번노드에 연결
        (pList->nodeNum)++;
    }
    else {                              //마지막노드에 노드를 추가할 경우
        temp= pList->head;              //포인터 구조체가 1번 노드를 가르킴
        do{
            temp =temp->next;           //다음 노드로 이동
        }while(temp->next != pList->head);      //마지막 노드가 헤드를 가르킬때까지 이동
        temp->next = newNode;                   //마지막 노드에 새로운 노드를 연결
        newNode->next=pList->head;              //새로운 노드를 1번 노드에 연결
        (pList->nodeNum)++;
    }
}

//노드 중간에 삽입
void ListmidAdd(ListHead * pList, char *c, ListNode * prev){
    ListNode * pNode;
    ListNode * newNode =(ListNode *)malloc(sizeof(ListNode));
    strcpy(newNode->data, c);
    newNode->next = NULL;
    pNode= pList->head;                     //1번 노드를 가르킴
    while(pNode !=prev){                    //삽입하려는 노드까지 이동
        pNode= pNode->next;                 //다음 노드로 이동
    }
    newNode->next= pNode->next;             //새로운 노드를 다음 노드에 연결
    pNode->next= newNode;                   //삽입하는 위치 노드를 새로운 노드에 연결
    (pList->nodeNum)++;
}

//노드 탐색
ListNode * ListFind(ListHead *pList, char *c){
    ListNode *pNode;
    pNode = pList->head;                    //1번 노드를 가르킴
    do {
        if(strcmp(pNode->data,c)==0){       //노드안에 있는 데이터와 탐색하려는 데이터가 같은지 비교
            printf("탐색 성공\n\n");
            return pNode;                   //해당 노드 반환
        }
        pNode= pNode->next;                 //다음 노드로 이동
    }while(pNode != pList->head);           //1번노드가 나올때 까지 이동
    printf("탐색 실패\n\n");                //탐색 실패할 경우 출력
    return NULL;                            //NULL반환
}

//노드 삭제
void ListNodeRemove(ListHead *pList, ListNode *prev){
    ListNode * pNode;
    pNode= pList->head;                     //1번 노드를 가르킴
    if (prev == NULL) return;               //삭제할 노드가 없는경우
    else if(pList->head ==prev) {           //1번 노드를 삭제할 경우
        pList->head=prev->next;             //헤드 포인터 구조체를 2번 노드를 가르킴
        pNode = pList->head;                //2번 노드를 가르킴
        do{
            pNode=pNode->next;              //다음 노드로 이동
        }while(pNode->next != prev);        //2번 노드를 가르키는 포인터 구조제가 1번 노드를 만날때 까지 이동
        pNode->next = pList->head;          //마지막 노드를 2번 노드와 연결
        free(prev);                         //1번 노드 동적할당 제거
        (pList->nodeNum)--;
    }
    else {
        while(pNode->next != prev){         //제거할 노드 까지 이동
            pNode= pNode->next;             //다음 노드로 이동
        }
        pNode->next = prev->next;           //제거할 노드의 전 노드를 다음 노드와 연결
        free(prev);                         //제거할 노드 동적할당 제거
        (pList->nodeNum)--;
    }
}

int main(void){
    ListHead * list;
    ListNode * node;

    printf("공백리스트 추가\n");
    list= ListInit(list);
    printList(list);
    ListNodeNum(list);

    printf("\"자\"노드 추가\n");
    ListNodeAdd(list,"자",1);
    printList(list);
    ListNodeNum(list);

    printf("\"료\"노드 추가\n");
    ListNodeAdd(list,"료",2);
    printList(list);
    ListNodeNum(list);

    printf("\"한\"노드를 맨 앞에 추가\n");
    ListNodeAdd(list,"한",1);
    printList(list);
    ListNodeNum(list);

    printf("\"구\"노드 추가\n");
    ListNodeAdd(list,"구",2);
    printList(list);
    ListNodeNum(list);

    printf("\"료\"노드 탐색\n");
    node = ListFind(list,"료");

    printf("\"의\"노드를 \"료\"노드 뒤에 추가\n");
    ListmidAdd(list,"의",node);
    printList(list);
    ListNodeNum(list);

    printf("\"구\"노드 탐색\n");
    node = ListFind(list,"구");

    printf("\"조\"노드를 \"구\"노드 뒤에 추가\n");
    ListmidAdd(list,"조",node);
    printList(list);
    ListNodeNum(list);

    printf("\"의\" 노드 탐새 후 제거 \n");
    node = ListFind(list, "의");		// 삭제할 노드 위치 pNode를 찾음
    ListNodeRemove(list, node);			// 포인터 pNode 노드 삭제
    printList(list);
    ListNodeNum(list);

    printf("\"한\"노드 탐색 후 제거\n");
    node = ListFind(list,"한");
    ListNodeRemove(list, node);
    printList(list);
    ListNodeNum(list);

    free(list); // 동적할당 제거
    free(node); // 동적할당 제거
    return 0;
}