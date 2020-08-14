#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

//트리 노드
typedef struct _BtreeNode{
    int data;
    struct _BtreeNode * left;
    struct _BtreeNode * right;
}BTreeNode;

//트리 노드 기반의 스택 노드
typedef struct _StackNode{
    BTreeNode * Node;
    struct _StackNode * next;
}StackNode;

//스택
typedef struct _stack{
    StackNode * head;
}Stack;

//트리 노드 기반의 큐 노드
typedef struct _QueueNode{
    BTreeNode * Node;
    struct _QueueNode * next;
}QueueNode;

//큐
typedef struct _queue{
    QueueNode * front;
    QueueNode * rear;
}Queue;

//트리노드 생성 및 초기화
BTreeNode * MakeBTreeNode(void){
    BTreeNode * newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    newNode->right = NULL;
    newNode->left = NULL;
    return newNode;
}

//트리노드 데이터 설정
void setdata(BTreeNode * bt, int data){
    bt->data = data;
}

//트리노드 데이터 출력
int getData(BTreeNode * bt){
    return bt->data;
}

//왼쪽 서브 트리 설정
void MakeLeftSubTree(BTreeNode * main, BTreeNode * sub){
    if(main->left != NULL){
        free(main->left);
    }
    main->left = sub;
}

//오른쪽 서브 트리 설정
void MakeRightSubTree(BTreeNode * main, BTreeNode * sub){
    if(main->right != NULL){
        free(main->right);
    }
    main->right = sub;
}

//스택 초기화
void StackInit(Stack * stack){
    stack->head = NULL;
}

//스택이 공백리스트인지 확인
int StackIsEmpty(Stack *stack){
    if(stack->head == NULL)
        return TRUE;
    else
        return FALSE;
}

//스택에 노드 추가(트리 노드 기반)
void SPush(Stack * stack, BTreeNode * bt){
    StackNode * newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->Node = bt;
    newNode->next = stack->head;
    stack->head = newNode;
}

//스택에서 노드 꺼내기
BTreeNode * SPop(Stack *stack){
    StackNode * SNode = stack->head;
    BTreeNode * BTreeNode = stack->head->Node;

    if(StackIsEmpty(stack)){                //비어있는 상태에서 Pop 할 경우 오류 출력
        printf("오류");
        exit(-1);
    }
    stack->head = SNode->next;
    free(SNode);
    return BTreeNode;
}

//스택에서 정보 출력
BTreeNode * SPeek(Stack *stack){
    if(StackIsEmpty(stack)){
        return NULL;
    }
    return stack->head->Node;
}

//큐 초기화
void QueueInit(Queue * q){
    q->front = NULL;
    q->rear = NULL;
}

//큐가 공백리스트 인지 확인
int QueueIsEmpty(Queue * q){
    if(q->front == NULL)
        return TRUE;
    else
        return FALSE;
}

//큐에 노드 추가(트리 노드 기반)
void Enqueue(Queue * q, BTreeNode * bt){
    QueueNode * newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->Node = bt;
    newNode->next = NULL;

    if(QueueIsEmpty(q)){
        q->front = newNode;
        q->rear = newNode;
    }
    else{
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

//큐에서 노드 꺼내기
BTreeNode * Dequeue(Queue * q){
    QueueNode * QNode = q->front;
    BTreeNode * BTreeNode = QNode->Node;
    if(QueueIsEmpty(q)){
        printf("오류");
        exit(-1);
    }
    q->front = QNode->next;
    free((QNode));
    if(q->front == NULL){
        q->rear = NULL;
    }
    return BTreeNode;
}

//스택과 반복문을 통한 전위 순회
void PreorderTraverse(BTreeNode * bt){
    Stack stack;                        //스택 선언
    StackInit(&stack);                  //스택 초기화
    BTreeNode * start = bt;             //시작점 설정
    BTreeNode * nextN;
    int data;
    SPush(&stack, start);               //스택에 시작노드 추가

    printf("preorder : ");

    /*루트 노드에서 시작해서 출력 순서에 맞게 스택에
        노드를 저장하면서 자식노드로 내려감 */
    while(!StackIsEmpty(&stack)){       //스택이 비워질때 까지 반복
        nextN = SPop(&stack);           //스택에 있는 노드 꺼내기
        data = getData(nextN);          //데이터 출력
        printf("%c ", data + 65);
        if(nextN->left != NULL || nextN->right != NULL) {               //스택에서 꺼내온 노드가 단말 노드가 아닐때
            if(nextN->right == NULL) {                                  //노드의 자식이 왼쪽만 있는 경우
                SPush(&stack, nextN->left);                             //오른쪽은 NULL이므로 왼쪽만 추가
            }
            else if(nextN->left == NULL) {                              //노드의 자식이 오른쪽만 있는 경우
                SPush(&stack, nextN->right);                            //왼쪽은 NULL이므로 오른쪽만 추가
            }
            else {                                                      //노드의 자식이 오른쪽, 왼쪽 전부 있을경우
                SPush(&stack, nextN->right);                            //스택의 특징 때문에 오른쪽 먼저 저장
                SPush(&stack, nextN->left);
            }
        }
    }
    printf("\n");
    printf("\n");
}

//스택과 반복문을 통한 중위 순회
void InorderTraverse(BTreeNode * bt){
    Stack stack;                        //스택 선언
    StackInit(&stack);                  //스택 초기화
    BTreeNode * start = bt;             //시작점 설정
    BTreeNode * nextN = start;
    int data;

    printf("Inorder : ");

    /*루트 노드에서 시작하지만 출력은 자식노드가 먼저
      출력 되므로 제일 왼쪽 끝에 있는 노드로 이동하면서 내부 노드 저장*/
    while(TRUE){
        while (nextN != NULL){              //제일 왼쪽 끝에 있는 노드로 이동, 단말노드가 아닐때 까지 반복
            SPush(&stack, nextN);           //이동중 내부 노드 저장
            nextN = nextN->left;            //왼쪽 노드로 이동
        }
        if(!StackIsEmpty(&stack)){          //스택이 공백이면 루프 정지
            nextN = SPop(&stack);           //스택에 저장된 노드 꺼내기
            data = getData(nextN);          //데이터 출력
            printf("%c ", data + 65);

            nextN = nextN->right;           /*만약 단말노드이거나 오른쪽이 없으면 NULL이 저장되고
                                                 첫번째 루프를 실행하지 않고 넘어가고 바로출력됨*/
        }
        else{
            break;
        }
    }
    printf("\n");
    printf("\n");
}

//스택과 반복문을 통한 후위 순회
void PostorderTraverse(BTreeNode * bt){
    Stack stack;                          //스택 선언
    StackInit(&stack);                    //스택 초기화
    BTreeNode * start = bt;               //시작점
    BTreeNode * nextN = start;
    int data;
    SPush(&stack, nextN);

    printf("Postorder : ");

    /*루트 노드에서 시작하지만 출력은 자식노드가 먼저
     출력 되므로 제일 왼쪽 끝에 있는 노드로 이동하면서 내부 노드 저장*/
    while (!StackIsEmpty(&stack)){         //스택이 비워질때 까지 반복
        while (nextN != NULL) {            //제일 왼쪽 끝에 있는 노드로 이동, 단말노드가 아닐때 까지 반복
            if (nextN->right != NULL)      //오른쪽 노드가 있으면 오른쪽 노드를 스택에 추가
                SPush(&stack, nextN->right);
            SPush(&stack, nextN);          //이동중 내부 노드 저장
            nextN = nextN->left;           //왼쪽 노드로 이동
        }
        nextN = SPop(&stack);              //스택에 저장된 노드 꺼내기
        if (nextN->right != NULL && SPeek(&stack) == nextN->right) {     //오른쪽노드가 NULL이 아니고 스택에 저장된 노드와
                                                                         //자식노드가 같으면 실행
            SPop(&stack);                  //스택에 있는 노드 꺼내기(오른쪽 자식노드 꺼내기)
            SPush(&stack, nextN);          //다시 스택에 노드 저장
            nextN = nextN->right;          //오른쪽 노드로 이동
        } else if(SPeek(&stack)== NULL){   //스택이 공백이면 정지
            break;
        } else {
            data = getData(nextN);         //데이터 출력
            printf("%c ", data + 65);
            nextN = NULL;                  //이동하지 않음
        }
    }
    printf("\n");
    printf("\n");
}

//큐와 반복문을 통한 레벨 순회
void LevelTraverse(BTreeNode * bt){
    Queue queue;                        //큐 선언
    QueueInit(&queue);                  //큐 초기화
    BTreeNode * start = bt;             //시작점 설정
    BTreeNode * nextN = start;
    int data;
    Enqueue(&queue, nextN);

    printf("Level : ");

    /*루트 노드에서 시작해서 출력 순서에 맞게 큐에
       노드를 저장하면서 자식노드로 내려감 */
    while(!QueueIsEmpty(&queue)){       //큐가 비워질때 까지 반복
        nextN = Dequeue(&queue);        //큐에 있는 노드 꺼내기
        data = getData(nextN);          //데이터 출력
        printf("%c ", data + 65);
        if(nextN->left != NULL || nextN->right != NULL) {               //스택에서 꺼내온 노드가 단말 노드가 아닐때
            if(nextN->right == NULL) {                                  //노드의 자식이 왼쪽만 있는 경우
                Enqueue(&queue, nextN->left);                           //오른쪽은 NULL이므로 왼쪽만 추가
            }
            else if(nextN->left == NULL) {                              //노드의 자식이 오른쪽만 있는 경우
                Enqueue(&queue, nextN->right);                          //왼쪽은 NULL이므로 오른쪽만 추가
            }
            else {                                                      //노드의 자식이 오른쪽, 왼쪽 전부 있을경우
                Enqueue(&queue, nextN->left);                           //큐의 특징 때문에 왼쪽 먼저 저장
                Enqueue(&queue, nextN->right);
            }
        }
    }
    printf("\n");
    printf("\n");
}

int main(void){
    //트리 노드 생성
    BTreeNode * bt1 = MakeBTreeNode();
    BTreeNode * bt2 = MakeBTreeNode();
    BTreeNode * bt3 = MakeBTreeNode();
    BTreeNode * bt4 = MakeBTreeNode();
    BTreeNode * bt5 = MakeBTreeNode();
    BTreeNode * bt6 = MakeBTreeNode();
    BTreeNode * bt7 = MakeBTreeNode();
    BTreeNode * bt8 = MakeBTreeNode();
    BTreeNode * bt9 = MakeBTreeNode();
    BTreeNode * bt10 = MakeBTreeNode();
    BTreeNode * bt11 = MakeBTreeNode();

    //노드의 데이터 설정
    setdata(bt1 , 0);
    setdata(bt2 , 1);
    setdata(bt3 , 2);
    setdata(bt4 , 3);
    setdata(bt5 , 4);
    setdata(bt6 , 5);
    setdata(bt7 , 6);
    setdata(bt8 , 7);
    setdata(bt9 , 8);
    setdata(bt10 , 9);
    setdata(bt11 , 10);


    //노드를 연결하여 이진트리 생성
    MakeLeftSubTree(bt1,bt2);
    MakeRightSubTree(bt1,bt3);
    MakeLeftSubTree(bt2,bt4);
    MakeRightSubTree(bt2,bt5);
    MakeLeftSubTree(bt3,bt6);
    MakeRightSubTree(bt3,bt7);
    MakeLeftSubTree(bt4,bt8);
    MakeLeftSubTree(bt5,bt9);
    MakeRightSubTree(bt5,bt10);
    MakeRightSubTree(bt7,bt11);

    //순회 구현
    PreorderTraverse(bt1);
    InorderTraverse(bt1);
    PostorderTraverse(bt1);
    LevelTraverse(bt1);
}