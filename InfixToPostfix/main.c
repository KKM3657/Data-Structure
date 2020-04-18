#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct _Node{
    char data;
    struct _Node * next;
}Node;

typedef struct _List{
    Node * head;
}StackList;

typedef StackList Stack;
//스택 초기화 함수
void StackInit(Stack *pStack){
    pStack->head =NULL;
}
//스택이 비워져있는지 확인하는 함수
int SIsEmpty(Stack *pStack){
    if(pStack->head == NULL)
        return TRUE;
    else
        return FALSE;
}
//스택에 정보 입력 함수
void SPush(Stack *pStack, char c){
    Node * newNode = (Node*)malloc(sizeof(Node));
    newNode->data = c;
    newNode->next = pStack->head;
    pStack->head = newNode;
}
//스택에서 맨 위에있는 정보를 출력후 제거 함수
char SPop(Stack *pStack){
    char  popOp;
    if(SIsEmpty(pStack)){
        printf("Stack memory Error");
        exit(-1);
    }
    Node * pNode = pStack->head;
    popOp = pNode->data;
    pStack->head= pNode->next;
    free(pNode);
    return popOp;
}
//스택에서 맨 위에있는 정보 출력 함수
char SPeek(Stack *pStack){
    if(pStack->head ==NULL){
        return 0;
    }
    char  popOp = pStack->head->data;
    return popOp;
}
//연산자 우선순위 정의 함수
int GetOpPrec(char c){
    switch(c){
        case '*':
        case '/':
            return 3;
        case '+':
        case '-':
            return 2;
        case '(':
            return 1;
        default:
            break;
    }
    return -1;
}
//연산자 우선순위 비교 함수
int WhoPrecOp(char c1, char c2){
    int Op1 = GetOpPrec(c1);
    int Op2 = GetOpPrec(c2);

    if(Op1 > Op2){          //Op1이 Op2보다 우선순위가 높을경우 1출력
        return 1;
    }
    else if(Op1 < Op2){     //Op1이 Op2보다 우선순위가 작을경우 -1출력
        return -1;
    }
    else{                   //Op1이 Op2와 우선순위가 같을경우 0출력
        return 0;
    }
}
//중위 표기식을 후위 표기식으로 변환 하는 함수
char * infixToPostfix(char *exp){
    Stack stack;                    //스택 정의
    int expLen = strlen(exp);       //문자열의 길이 저장
    char * convExp = (char*)malloc(sizeof(char)*expLen+1);          //후위 표기식으로 저장하는 메모리 할당

    int i ,idx =0;
    char  tok, popOp;

    memset(convExp, 0, sizeof(char)*expLen+1);              //후위 표기식 저장하는 메모리를 0으로 초기화
    StackInit(&stack);                                      //스택 초기화

    for(i=0; i<expLen;i++){                                 //문자열 길이 만큼 반복
        tok = exp[i];                                       //문자열을 문자 1개 단위로 저장
        if(isdigit(tok)){                                   //저장한 변수값이 숫자인지 판별
            convExp[idx++]= tok;                            //숫자일경우 후위 표기식 메모리에 저장
        }
        else{                                               //저장한 변수값이 연산자일 경우
            switch(tok) {
                case '(':                                   //case 1: '('일 경우
                    SPush(&stack, tok);                     //스택에 문자 저장
                    break;
                case ')':                                   //case 2: ')'일 경우
                   while(TRUE){                             //'('가 출력될때 까지 반복
                       popOp = SPop(&stack);                //정보를 출력후 제거(Pop)
                       if(popOp == '('){                    //출력한 정보가 '('일 경우 중단
                           break;
                       }
                       convExp[idx++]=popOp;                //출력한 정보를 후위 표기식 메모리에 저장
                   }
                   break;
                case '+': case '-':                         //case 3: 산술 연산자일 경우
                case '*': case '/':                                                     //스택이 비워져있을경우 중단
                       while(!SIsEmpty(&stack) && WhoPrecOp(SPeek(&stack),tok) >= 0){   //스택에 저장된 연산자와 변수에 저장된 연산자의 우선순위 비교후
                            convExp[idx++]= SPop(&stack);                               //-1이 나오지 않을떄 까지 반복 그리고 출력
                       }
                       SPush(&stack, tok);                  //연산자를 스택에 저장함
                       break;
            }
        }
    }
    while(!SIsEmpty(&stack))                                //스택에 남아있는 연산자를 후위 표기식 메모리에 모두 저장
        convExp[idx++] = SPop(&stack);

    free(exp);                                              //기존 중위 표기식 문자열을 동적 제거
    exp = convExp;                                          //후위 표기식 메모리를 가르킴
    return exp;                                             //후위 표기식 메모리 주소 반환
}
//후위 표기식 계산 함수
int evalPostfix(char *exp){
    Stack stack;                                            //스택 정의
    int expLen = strlen(exp);                               //후위 표기식 문자열 길이 저장
    int i;
    char tok, op1, op2;

    StackInit(&stack);                                      //스택 초기화

    for(i= 0;i<expLen;i++){                                 //후위 표기식 문자열 길이 만큼 반복
        tok = exp[i];                                       //문자열을 문자 1개 단위로 저장
        if(isdigit(tok)){                                   //저장한 변수값이 숫자인지 판별
            SPush(&stack, tok - '0');                    //저장한 변수값을 스택에 저장(정수 형태로)
        } else{                                             //연산자일 경우
            op2 =SPop(&stack);                              //스택에서 숫자 출력1
            op1 =SPop(&stack);                              //스택에서 숫자 출력2
        }
        switch(tok){
            case '+':                                       //case 1 : 덧셈일경우
                SPush(&stack,op1+op2);
                break;
            case '-':                                       //case 2 : 뺄셈일경우
                SPush(&stack,op1-op2);
                break;
            case '*':                                       //case 3 : 곱셈일경우
                SPush(&stack,op1*op2);
                break;
            case '/':                                       //case 4 : 나눗셈일경우
                SPush(&stack,op1/op2);
                break;
        }
    }
    return SPop(&stack);                                    //결과값 출력
}

int main(void){
    int result;
    char* express = "((2-5)+(3*4-1)-(9/3))";      // 중위 연산식

    printf("중위 표기식 : %s ", express);

    express=infixToPostfix(express);                  // 후위 표기법
    printf("후위 표기식 : %s", express);

    result = evalPostfix(express);                    // 후위 연산식 계산
    printf("\n\n연산 결과 => %d", result);

    getchar();

    return 0;
}