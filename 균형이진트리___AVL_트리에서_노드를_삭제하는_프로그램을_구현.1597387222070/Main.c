#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

typedef struct avl_node {
    struct avl_node *left_child, *right_child;  /* Subtrees. */
    int data;                   /* Pointer to data. */
} AVL_node;

AVL_node *root;
typedef void (*DPFun)(int);

AVL_node * MakeBTreeNode(void){
    AVL_node * node = (AVL_node*)malloc(sizeof(AVL_node));
    node->left_child = NULL;
    node->right_child = NULL;
    return node;
}
// 오른쪽 회전 함수
AVL_node *
rotate_right(AVL_node *parent)
{
    AVL_node *child = parent->left_child;
    parent->left_child = child->right_child;
    child->right_child = parent;
    return child;
}
// 왼쪽 회전 함수
AVL_node *
rotate_left(AVL_node *parent)
{
    AVL_node *child = parent->right_child;
    parent->right_child = child->left_child;
    child->left_child = parent;
    return child;
}
// 오른쪽-왼쪽 회전 함수
AVL_node *
rotate_right_left(AVL_node *parent)
{
    AVL_node *child = parent->right_child;
    parent->right_child = rotate_right(child);
    return rotate_left(parent);
}
// 왼쪽-오른쪽 회전 함수
AVL_node *
rotate_left_right(AVL_node *parent)
{
    AVL_node *child = parent->left_child;
    parent->left_child = rotate_left(child);
    return rotate_right(parent);
}
// 트리의 높이를 반환
int get_height(AVL_node *node)
{
    int height=0;
    if( node != NULL )
        height = 1 + fmax(get_height(node->left_child),	get_height(node->right_child));
    return height;
}

// 노드의 균형인수를 반환
int get_height_diff(AVL_node *node)
{
    if( node == NULL ) return 0;
    return get_height(node->left_child) - get_height(node->right_child);
}

// 트리를 균형트리로 만든다
AVL_node *
rebalance(AVL_node **node)
{
    int height_diff = get_height_diff(*node);            // 균형 인수 계산
    // 균형 인수가 +2 이상이면 LL 상태 또는 LR 상태
    if( height_diff > 1 ){        // 왼쪽 서브 트리 방향으로 높이가 2 이상 크다면,
        if( get_height_diff((*node)->left_child) > 0 )
            *node = rotate_right(*node);            // LL
        else
            *node = rotate_left_right(*node);       // LR
    }
        // 균형 인수가 -2 이상이면 RR 상태 또는 RL 상태
    else if ( height_diff < -1 ){     // 오른쪽 서브 트리 방향으로 높이가 2 이상 크다면,
        if( get_height_diff((*node)->right_child) < 0 )
            *node = rotate_left(*node);             // RR
        else
            *node = rotate_right_left(*node);       // RL
    }
    return *node;
}

// AVL 트리의 삽입 연산
AVL_node *
avl_add(AVL_node **root, int new_key)
{
    if( *root == NULL ){
        *root = (AVL_node *)
                malloc(sizeof(AVL_node));
        if( *root == NULL ){
            fprintf(stderr, "메모리 할당 에러\n");
            exit(1);
        }
        (*root)->data = new_key;
        (*root)->left_child = (*root)->right_child = NULL;
    }
    else if( new_key < (*root)->data ){
        (*root)->left_child=avl_add(&((*root)->left_child), new_key);
        *root = rebalance(root);
    }
    else if( new_key > (*root)->data ){
        (*root)->right_child=avl_add(&((*root)->right_child), new_key);
        (*root) = rebalance(root);
    }
    else{
        fprintf(stderr, "중복된 키 에러\n");
        exit(1);
    }
    return *root;
}

//AVL 트리에서 키값과 같은 노드를 찾아 삭제하는 연산
void deleteNode(AVL_node **pRoot, int key) {
    AVL_node *pVRoot = MakeBTreeNode();         //가상노드
    AVL_node *pNode = pVRoot;                   //부모노드
    AVL_node *cNode = *pRoot;                   //현재노드
    AVL_node *dNode;                            //삭제할 노드

    pVRoot->right_child = *pRoot;               //가상노드의 자식이 루트노드

    // 삭제할 노드가 없는 경우
    if (cNode == NULL) {
        printf("\n 찾는 키가 이진 트리에 없습니다!!");
        return;
    }
    dNode = cNode;                              //삭제할 노드를 지정

    // 삭제할 노드가 단말 노드인 경우
    if ((cNode->left_child == NULL) && (cNode->right_child == NULL)) {
        if (pNode->left_child == dNode) {
            pNode->left_child = NULL;
            printf("%d 삭제\n", dNode->data);
            free(dNode);
        } else {
            pNode->right_child = NULL;
            printf("%d 삭제\n", dNode->data);
            free(cNode);
        }
    }

    // 삭제할 노드가 자식 노드를 한 개 가진 경우
    else if ((cNode->left_child == NULL) || (cNode->right_child == NULL)) {
        AVL_node * dcNode;
        if (dNode->left_child != NULL)
            dcNode = pNode->left_child;
        else
            dcNode = pNode->right_child;

        if(pNode->left_child == dNode){
            pNode->left_child = dcNode;
            printf("%d 삭제\n", dNode->data);
            free(dNode);
        }
        else{
            pNode->right_child = dcNode;
            printf("%d 삭제\n", dNode->data);
            free(dNode);
        }
    }

    // 삭제할 노드가 자식 노드를 두 개 가진 경우
    else {
        AVL_node * mNode = dNode->right_child;
        AVL_node * mpNode = dNode;
        int delData;

        while(mNode->left_child != NULL){
            mpNode = mNode;
            mNode = mNode->left_child;
        }
        delData = dNode->data;
        dNode->data = mNode->data;

        if(mpNode->left_child == mNode)
            mpNode->left_child = mNode->right_child;
        else
            mpNode->right_child = mNode->right_child;

        dNode = mNode;
        printf("%d 삭제\n", delData);
        free(dNode);
    }
    //삭제할 노드가 루트노드 일경우
    if(pVRoot->right_child != *pRoot)
        *pRoot = pVRoot->right_child;

}

// AVL 트리에서 삭제할 노드 탐색
AVL_node * avl_delete(AVL_node **root, int new_key) {
    if( (*root)->data == new_key ){             //key를 이용해서 삭제할 노드인지 판별
        if( *root == NULL ){
            fprintf(stderr, "메모리 할당 에러\n");
            exit(1);
        }
        deleteNode(root, new_key);              //삭제할 노드
    }
    else if( new_key < (*root)->data ){         //key 값이 해당노드보다 작을경우 왼쪽 자식으로 이동
        (*root)->left_child=avl_delete(&((*root)->left_child), new_key);
        *root = rebalance(root);                //균형인수 확인후 균형
    }
    else if( new_key > (*root)->data ){         //key 값이 해당노드보다 클 경우 오른쪽 자식으로 이동
        (*root)->right_child=avl_delete(&((*root)->right_child), new_key);
        (*root) = rebalance(root);              //균형인수 확인후 균형
    }
    else{
        fprintf(stderr, "삭제 에러 - 노드 탐색 불가\n");
        exit(1);
    }
    return *root;
}

// AVL 트리의 탐색함수
AVL_node *avl_search(AVL_node *node, int key)
{
    if( node == NULL ) return NULL;
    printf("%d ", node->data);
    if( key == node->data ) return node;
    else if( key < node->data )
        return avl_search(node->left_child, key);
    else
        return avl_search(node->right_child, key);
}
//중위선회
void InorderTraverse(AVL_node *bt, DPFun action){
    if(bt == NULL) {
        return;
    }
    InorderTraverse(bt->left_child, action);                  //재귀를 이용하여 왼쪽노드로 이동함
    action(bt->data);                                         //함수 포인터를 이용하여 ShowCharData함수 호출
    InorderTraverse(bt->right_child, action);                 //재귀를 이용하여 오른쪽 노드를 이용함
}
//데이터 출력 함수
void ShowCharData(int data){
    printf(" %d", data);
}
int main()
{
    //7,8,9,2,1,5,3,6,4 삽입
    avl_add(&root, 7);
    avl_add(&root, 8);
    avl_add(&root, 9);
    avl_add(&root, 2);
    avl_add(&root, 1);
    avl_add(&root, 5);
    avl_add(&root, 3);
    avl_add(&root, 6);
    avl_add(&root, 4);

    printf("inorder :");
    InorderTraverse(root, ShowCharData);
    printf("\n");

    printf("탐색과정 : ");
    avl_search(root, 6);
    printf("\n");
    avl_delete(&root,5);
    printf("\n");

    printf("inorder :");
    InorderTraverse(root, ShowCharData);
    printf("\n");
    printf("탐색과정 : ");
    avl_search(root, 4);

    return 0;
}

