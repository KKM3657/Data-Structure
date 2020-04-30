#include <stdio.h>
#include <stdlib.h>

typedef struct _BTreeNode{
    char data;
    struct _BTreeNode * left;
    struct _BTreeNode * right;
}BTNode;

typedef void (*DPFun)(char);                                //함수 포인터 선언
typedef void (*NPFun)(BTNode *, int *);                     //함수 포인터 선언

//이진트리 노드 생성 및 초기화 함수
BTNode * BTreeNodeMake(void){
    BTNode * bt = (BTNode*)malloc(sizeof(BTNode));
    bt->left = NULL;
    bt->right = NULL;
    return bt;
}

//이진트리 노드 데이터 저장 함수
void SetData(BTNode * bt, char data){
    bt->data = data;
}

//이진트리 왼쪽노드 연결 함수
void MakeLeftSubTree(BTNode * main, BTNode * sub){
    if(main->left != NULL){
        free(main->left);
    }
    main->left = sub;
}

//이진트리 오른쪽노드 연결 함수
void MakeRightSubTree(BTNode * main, BTNode * sub){
    if(main->right != NULL){
        free(main->right);
    }
    main->right = sub;
}

//이진트리 전위 순회 함수
void PreorderTraverse(BTNode * bt, DPFun action){
    if(bt == NULL){
        return;
    }
    action(bt->data);                                   //함수 포인터를 이용하여 ShowCharData함수 호출
    PreorderTraverse(bt->left,action);                  //재귀를 이용하여 왼쪽 노드로 이동함
    PreorderTraverse(bt->right,action);                 //재귀를 이용하여 오른쪽 노드로 이동함
}

//이진트리 중위 순회 함수
void InorderTraverse(BTNode *bt, DPFun action){
    if(bt == NULL) {
        return;
    }
    InorderTraverse(bt->left, action);                  //재귀를 이용하여 왼쪽노드로 이동함
    action(bt->data);                                   //함수 포인터를 이용하여 ShowCharData함수 호출
    InorderTraverse(bt->right, action);                 //재귀를 이용하여 오른쪽 노드를 이용함
}

//이진트리 후위 순회 함수
void PostorderTraverse(BTNode * bt, DPFun action){
    if(bt == NULL){
        return;
    }
    PostorderTraverse(bt->left, action);                //재귀를 이용하여 왼쪽노드로 이동
    PostorderTraverse(bt->right, action);               //재귀를 이용하여 오른쪽노드로 이동
    action(bt->data);                                   //함수 포인터를 이용하여 ShowCharData함수 호출
}

//이진트리 노드 개수 함수
void BTreeNodeNum(BTNode *bt, int *count, NPFun action){
    if(bt == NULL){
        return;
    }                                                   //함수포인터를 이용하여 CountBTreeAllNode함수 호출
    action(bt, count);                                  //함수포인터를 이용하여CountBTreeTerminalNode함수 호출
    BTreeNodeNum(bt->left,count, action);               //재귀를 이용하여 왼쪽노드로 이동
    BTreeNodeNum(bt->right,count, action);              //재귀를 이용하여 오른쪽노드로 이동
}

//이진트리 높이 함수
int BTreeHeight(BTNode *bt, int *height){
    int max;
    int result1,result2;
    if(bt== NULL){
        return 0;
    }

    result1=BTreeHeight(bt->left, height);              //이진트리에서 왼쪽노드의 높이
    result2=BTreeHeight(bt->right, height);             //이진트리에서 오른쪽노드의 높이

    max= result1>=result2 ? result1 : result2;          //왼쪽노드와 오른쪽노드를 비교해서 큰 값을 max에 저장
    *height = max +1;                                   //높이는 max+1
    return *height;                                     //높이 반환
}

//데이터 출력 함수
void ShowCharData(char data){
    printf(" %c", data);
}

//이진트리 노드 개수 함수
void CountBTreeAllNode(BTNode * bt, int *count){
    if(bt != NULL)
        (*count)++;
}

//이진트리 단말 노드 개수 함수
void CountBTreeTerminalNode(BTNode * bt, int *count){
    if(bt->left == NULL && bt->right == NULL){          //단말 노드일때 개수 증가
        (*count)++;
    }
}

int main(void){
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;

    //노드 생성
    BTNode * bt1 = BTreeNodeMake();
    BTNode * bt2 = BTreeNodeMake();
    BTNode * bt3 = BTreeNodeMake();
    BTNode * bt4 = BTreeNodeMake();
    BTNode * bt5 = BTreeNodeMake();
    BTNode * bt6 = BTreeNodeMake();
    BTNode * bt7 = BTreeNodeMake();
    BTNode * bt8 = BTreeNodeMake();
    BTNode * bt9 = BTreeNodeMake();
    BTNode * bt10 = BTreeNodeMake();
    BTNode * bt11 = BTreeNodeMake();

    //노드의 데이터 설정
    SetData(bt1 , 'A');
    SetData(bt2 , 'B');
    SetData(bt3 , 'C');
    SetData(bt4 , 'D');
    SetData(bt5 , 'E');
    SetData(bt6 , 'F');
    SetData(bt7 , 'G');
    SetData(bt8 , 'H');
    SetData(bt9 , 'I');
    SetData(bt10 , 'J');
    SetData(bt11 , 'K');

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

    //전위 순회
    printf("preorder :");
    PreorderTraverse(bt1, ShowCharData);
    printf("\n");
    printf("\n");

    //중위 순회
    printf("inorder :");
    InorderTraverse(bt1, ShowCharData);
    printf("\n");
    printf("\n");

    //후위 순회
    printf("postorder :");
    PostorderTraverse(bt1, ShowCharData);
    printf("\n");
    printf("\n");

    //노드 개수 출력
    BTreeNodeNum(bt1, &count1, CountBTreeAllNode);
    printf("이진 트리 노드 개수: %d\n",count1);
    printf("\n");
    BTreeNodeNum(bt1, &count2, CountBTreeTerminalNode);
    printf("이진 트리 단말 노드 개수: %d\n",count2);
    printf("\n");
    BTreeHeight(bt1, &count3);
    printf("이진 트리의 높이: %d\n",count3);

}