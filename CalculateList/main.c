#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
    int coef;
    int expo;
    struct _Node *next;
}ListNode;
typedef struct _List{
    ListNode * head;
    int numOfData;
}ListHead;
//리스트 초기화
ListHead * ListInit(ListHead *pList){
    pList = (ListHead*)malloc(sizeof(ListHead));                //동적할당
    pList->head =NULL;                                          //가르키는 노드가 없음
    pList->numOfData =0;                                        //노드 갯수가 0
    return pList;
}
//리스트에 데이터 저장
void ListDataAdd(ListHead* pList,int d1,int d2){
    ListNode *newNode=(ListNode*)malloc(sizeof(ListNode));      //동적할당
    newNode->coef = d1;                                         //차항계수 정보 입력
    newNode->expo = d2;                                         //차항 정보 입력
    newNode->next = NULL;                                       //가르키는 노드가 없음
    ListNode *pNode;                                            //리스트를 가르키는 포인터 구조체를 설정

    if(pList->head == NULL){                                    //공백리스트 일 경우
        pList->head = newNode;                                  //헤드가 생성한 노드를 가르킴
        (pList->numOfData)++;                                   //노드 갯수 추가
        return;
    }
    else{                                                       //노드를 생성할때 마다 연결시킬때
        pNode=pList->head;                                      //pNode가 1번 노드를 가르킴
        while(pNode->next != NULL){                             //pNode가 마지막 노드를 가르킬 때 까지 반복
            pNode=pNode->next;                                  //다음 노드로 이동
        }
        pNode->next= newNode;                                   //마지막 노드가 생성한 노드를 가르킴
        (pList->numOfData)++;                                   //노드 갯수 추가
    }
}
//다항식 덧셈기
void ListCalculate(ListHead *aList,ListHead *bList,ListHead *cList){
    ListNode *aNode = aList->head;
    ListNode *bNode = bList->head;
    while((aNode != NULL) || (bNode != NULL)) {                 //A다항식과 B다항식이 NULL에 도달할때 까지 반복
        if(aNode == NULL && bNode != NULL){                     //A다항식이 끝나고 B다항식만 남아있을 경우
            ListDataAdd(cList,bNode->coef,bNode->expo);         //C다항식에 bNode가 가르키는 노드 정보를 추가
            bNode = bNode->next;                                //B다항식을 가르키는 bNode를 다음으로 이동
        }
        else if(aNode != NULL && bNode == NULL){                //B다항식이 끝나고 A다항식만 남아있을 경우
            ListDataAdd(cList, aNode->coef, aNode->expo);       //C다항식에 aNode가 가르키는 노드 정보를 추가
            aNode = aNode->next;                                //A다항식을 가르키는 aNode를 다음으로 이동
        }
        else if (aNode->expo > bNode->expo) {                   //A다항식이 최고차항이 B다항식 최고차항보다 클 경우
            ListDataAdd(cList, aNode->coef, aNode->expo);       //C다항식에 aNode가 가르키는 노드 정보를 추가
            aNode = aNode->next;                                //A다항식을 가르키는 aNode를 다음으로 이동
        }
        else if(aNode->expo < bNode->expo) {                    //B다항식이 최고차항이 A다항식 최고차항보다 클 경우
            ListDataAdd(cList,bNode->coef,bNode->expo);         //C다항식에 bNode가 가르키는 노드 정보를 추가
            bNode = bNode->next;                                //B다항식을 가르키는 bNode를 다음으로 이동
        }
        else{                                                   //A다항식의 최고차항 와 B다항식의 최고차항이 같을 경우
            ListDataAdd(cList,(aNode->coef)+(bNode->coef),aNode->expo); //C다항식에 aNode와bNode를 가르키는 노드 정보를 추가
            aNode = aNode->next;                                //A다항식을 가르키는 aNode를 다음으로 이동
            bNode = bNode->next;                                //B다항식을 가르키는 bNode를 다음으로 이동
        }
    }
}
// 리스트 출력 함수
void ListPrint(ListHead *pList){
    ListNode *pNode;
    pNode= pList->head;                                     //pNode가 1번 노드를 가르킴
    while(pNode != NULL){                                   //pNode가 마지막 노드를 가르킬때 까지 반복
        printf("%dx^%d ",pNode->coef,pNode->expo);          //노드 정보 출력
        pNode=pNode->next;                                  //pNode가 다음 노드로 이동
        if(pNode != NULL){                                  //노드가 끝날때 마다 +출력
            printf("+ ");
        }
    }
    printf("\n");
}

int main() {
    ListHead * aList;
    ListHead * bList;
    ListHead * cList;

    aList=ListInit(aList);              //공백리스트 생성
    bList=ListInit(bList);
    cList=ListInit(cList);

    ListDataAdd(aList,5,6);     //A 다항식 구현
    ListDataAdd(aList,3,4);
    ListDataAdd(aList,2,2);
    printf("A(x) = ");
    ListPrint(aList);

    ListDataAdd(bList,2,7);     //B 다항식 구현
    ListDataAdd(bList,2,4);
    ListDataAdd(bList,2,3);
    ListDataAdd(bList,7,1);
    ListDataAdd(bList,1,0);
    printf("B(x) = ");
    ListPrint(bList);

    ListCalculate(aList,bList,cList);    //C 다항식 구현
    printf("C(x) = ");
    ListPrint(cList);
    return 0;
}
