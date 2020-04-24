#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct _Node{
    char data;
    struct _Node * next;
    struct _Node * prev;
}Node;

typedef struct _Deque{
    Node * head;
    Node * tail;
}Deque;
//덱 초기화 함수
void * DequeInit(Deque *dQ){
    dQ->head = NULL;
    dQ->tail = NULL;
}
//덱이 공백인지 확인하는 함수
int DQIsEmpty(Deque *dQ){
    if(dQ->head == NULL)
        return TRUE;
    else
        return FALSE;
}
//덱에서 앞부분 정보 추가 함수
void DQAddFirst(Deque *dQ, char data){
    Node * newNode = (Node*)malloc(sizeof(Node));               //동적할당
    newNode->data = data;                                       //데이터 입력
    newNode->prev = NULL;                                       //NULL
    newNode->next = dQ->head;                                   //새로운 노드의 다음부분이 기존의 머리를 가리킴

    if(DQIsEmpty(dQ)){
        dQ->tail = newNode;                                     //공백일경우 첫노드 추가
    } else{
        dQ->head->prev = newNode;                               //기존노드의 첫부분이 새로운 노드를 가리킴
    }
    dQ->head = newNode;                                         //머리 부분 갱신
}
//덱에서 뒷부분 정보 추가 함수
void DQAddLast(Deque *dQ, char data){
    Node * newNode = (Node*)malloc(sizeof(Node));               //동적할당
    newNode->data = data;                                       //데이터 입력
    newNode->prev = dQ->tail;                                   //새로운 노드의 전 부분이 기존의 꼬리를 가리킴
    newNode->next = NULL;                                       //NULL

    if(DQIsEmpty(dQ)){
        dQ->head = newNode;                                     //공백일경우 첫노드 추가
    } else{
        dQ->tail->next = newNode;                               //기존노드의 꼬리부분이 새로운 노드를 가리킴
    }
    dQ->tail = newNode;                                         //꼬리 부분 갱신
}
//덱에서 앞부분 정보 삭제 함수
char DQRemoveFirst(Deque *dQ){
    Node * pNode = dQ->head;                                    //pNode가 머리부분을 가르킴
    char rdata;

    if(DQIsEmpty(dQ)){                                          //덱이 공백일 경우 오류 출력
        printf("오류 발생");
        exit(-1);
    }
    dQ->head = pNode->next;                                     //머리부분이 다음 노드로 이동
    rdata = pNode->data;                                        //삭제되는 노드의 정보 저장
    free(pNode);                                                //노드 삭제

    if(dQ->head == NULL){                                       //삭제 후 남은 노드가 없을 경우
        dQ->tail = NULL;
    }  else{
        dQ->head->prev = NULL;                                  //1번노드가 가리키는 전 노드는 NULL
    }
    return rdata;
}

char DQRemoveLast(Deque *dQ){
    Node * pNode = dQ->tail;                                    //pNode가 꼬리부분을 가르킴
    char rdata;

    if(DQIsEmpty(dQ)){                                          //덱이 공백일 경우 오류 출력
        printf("오류 발생");
        exit(-1);
    }
    dQ->tail = pNode->prev;                                     //꼬리부분이 전 노드로 이동
    rdata = pNode->data;                                        //삭제되는 노드의 정보 저장
    free(pNode);                                                //노드 삭제

    if(dQ->tail == NULL){                                       //삭제 후 남은 노드가 없을 경우
        dQ->head = NULL;
    } else{
        dQ->tail->next = NULL;                                  //꼬리노드가 가리키는 다음 노드는 NULL
    }
    return rdata;
}
//회문 판별 함수
int IsPalindrome(Deque * dQ1, Deque * dQ2){
    while(!DQIsEmpty(dQ1) && !DQIsEmpty(dQ2)){                  //공백이 아닐때 까지 비교
        char data1 = DQRemoveFirst(dQ1);
        char data2 = DQRemoveFirst(dQ2);

        if(data1 == data2){                                     //같은 문자 일 경우 넘어감
            continue;
        }
        else{
            return FALSE;                                       //하나라도 다르면 거짓 반환
        }
    }
    return TRUE;                                                //모든 문자가 다 같으면 참 반환
}
//회문 확인 함수
void Palindrome(char * exp){
    Deque convExp;
    Deque que1;
    Deque que2;

    int explen = strlen(exp);                                   //배열의 전체 길이 저장

    DequeInit(&convExp);                                        //덱 초기화
    DequeInit(&que1);                                           //덱 초기화
    DequeInit(&que2);                                           //덱 초기화

    int i,count;

    for(i =0, count =0; i<explen; i++){                         //배열의 정보를 덱에다가 저장
        if(exp[i] == ' '){                                      //띄어쓰기 일 경우 포함하지 않음
            continue;
        }else {                                                 //문자를 덱에다가 저장
            DQAddLast(&convExp, exp[i]);
            count++;                                            //문자 갯수
        }
    }

    if(count % 2 ==0) {                                         //문자 갯수가 짝수 일 경우
        for(i =0; i< (count/2); i++){
            DQAddLast(&que1,DQRemoveFirst(&convExp));           //덱에있는 첫노드를 새로운 덱에 저장
            DQAddLast(&que2,DQRemoveLast(&convExp));            //덱에있는 마지막노드를 새로운 덱에 저장
        }
        for(i=0; i<explen; i++){
            printf("%c",exp[i]);
        }
        printf("\n");
        if(IsPalindrome(&que1,&que2)) {                         //새로운 덱을 비교하여 회문인지 판별
            printf("회문입니다.\n\n");
        } else{
            printf("회문이 아닙니다.\n\n");
        }
    }
    else{                                                       //문자 갯수가 홀수 일 경우
        for(i =0; i< ((count-1)/2); i++){
            DQAddLast(&que1,DQRemoveFirst(&convExp));           //덱에있는 첫노드를 새로운 덱에 저장
            DQAddLast(&que2,DQRemoveLast(&convExp));            //덱에있는 마지막노드를 새로운 덱에 저장
        }
        for(i=0; i<explen; i++){
            printf("%c",exp[i]);
        }
        printf("\n");
        if(IsPalindrome(&que1,&que2)) {                         //새로운 덱을 비교하여 회문인지 판별
            printf("회문입니다.\n\n");
        } else{
            printf("회문이 아닙니다.\n\n");
        }
    }
}

int main(void){
    char str0[] = "madondam";
    char str1[] = "radar";
    char str2[] = "rotavator";
    char str3[] = "madam";
    char str4[] = "was it an cat i saw";
    char str5[] = "a man a plan a canal panama";
    char str6[] = "race car";
    char str7[] = "was it a cat i saw";
    char str8[] = "nurses run";
    char str9[] = "a man a plan an canal panama";

// Palindrome checker

    Palindrome(str0);
    Palindrome(str1);
    Palindrome(str2);
    Palindrome(str3);
    Palindrome(str4);
    Palindrome(str5);
    Palindrome(str6);
    Palindrome(str7);
    Palindrome(str8);
    Palindrome(str9);
    return 0;
}