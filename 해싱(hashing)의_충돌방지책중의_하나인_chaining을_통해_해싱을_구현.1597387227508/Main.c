#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TABLE_SIZE	7	// 해싱 테이블의 크기=소수
#define SIZE 20

//포인터 함수
typedef int (*HashFun)(int);

//Slot 데이터
typedef struct _Data{
    int data;
}Data;
//Slot
typedef struct _slot{
    int key;
    Data * value;
}Slot;
//Slot과 link를 포함한 노드
typedef struct _node{
    Slot data;
    struct _node * next;
}Node;
//key에 대한 연결리스트
typedef struct _list{
    Node * head;
    Node * tail;
}List;
//해쉬테이블
typedef struct _table{
    List tbl[TABLE_SIZE];
    HashFun hf;
}Table;

//리스트 초기화 함수
void ListInit(List * plist){
    plist->head = NULL;
    plist->tail = NULL;
}
//연결리스트 노드추가 함수
void ListInsert(List * plist, Slot data){
    Node * newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if(plist->head == NULL){
        plist->head = newNode;
        plist->tail = newNode;
    }
    else{
        plist->tail->next = newNode;
        plist->tail = newNode;
    }
}
//해쉬테이블 초기화 함수
void tableInit(Table * ht, HashFun f){
    for(int i =0; i< TABLE_SIZE; i++){
        ListInit(&(ht->tbl[i]));        //연결리스트를 NULL로 초기화
    }
    ht->hf = f;                         //해쉬함수 추가
}
//해쉬테이블 key 탐색 함수
int tableSearch(Table * ht, int key){
    int hv = ht->hf(key);
    Node * pNode;
    pNode = ht->tbl[hv].head;           //key에 해당하는 연결리스트를 가르키는 노드
    while(pNode != NULL){               //key에 해당하는 노드 탐색
        if(pNode->data.key == key){
            return key;
        }
        pNode = pNode->next;
    }
    return -1;
}
//해쉬테이블 정보 입력 핰수
void tableInsert(Table * ht, int key, Data * value){

    int hv = ht->hf(key);               //제산함수를 이용해서 해쉬 값 설정
    Slot pSlot = {key, value};          //key에 해당하는 value 저장

    if(tableSearch(ht, key) == key){
        printf("키 중복 입력\n");
        return;
    }
    else{
        ListInsert(&(ht->tbl[hv]), pSlot);      //해쉬테이블에 정보 입력
    }
}
//해쉬테이블 정보 출력
void tablePrint(Table * ht){
    Node * pNode;
    for(int i = 0; i< TABLE_SIZE; i++){
        pNode = ht->tbl[i].head;
        printf("[%d]->",i);
        while(pNode != NULL){
            printf("%d->",pNode->data.key);
            pNode = pNode->next;
        }
        printf("\n");
    }
}
//동적할당 및 데이터 저장
Data * MakeData(int data){
    Data * newData = (Data*)malloc(sizeof(Data));
    newData->data = data;
    return newData;
}
//해쉬 함수
int hash_function(int key)
{
    return key % TABLE_SIZE;
}

// 해싱 테이블을 사용한 예제
int main(void)
{
    int data[SIZE] = { 5, 8, 2, 13, 4, 6, 9, 11, 7 };

    Table DataTable;
    Data * dataP[10];
    memset(dataP,0,sizeof(dataP));

    tableInit(&DataTable, hash_function);

    //데이터 입력
    for(int i = 0; i < 9; i++){
        dataP[i] = MakeData(data[i]);
        tableInsert(&DataTable, data[i], dataP[i]);
    }
    printf("===========================\n");
    tablePrint(&DataTable);
    printf("===========================\n");
    
    //데이터 탐색
    for(int i = 0; i< 9; i++){
        if(tableSearch(&DataTable, data[i]) == data[i]){
            printf("탐색 %d 성공\n", data[i]);
        } else{
            printf("탐색 실패\n");
        }

    }
    if(tableSearch(&DataTable, 10) == -1){
        printf("탐색 %d 실패\n", 10);
    }
    return 0;
}