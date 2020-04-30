#include <stdio.h>
#include <stdlib.h>

typedef struct _bTreeNode{
    int data;
    struct _bTreeNode * left;
    struct _bTreeNode * right;
}BTreeNode;

BTreeNode * MakeTreeNode(void){
    BTreeNode * bt = (BTreeNode*)malloc(sizeof(BTreeNode));
    bt->left = NULL;
    bt->right = NULL;
    return bt;
}

int GetData(BTreeNode * bt){
    return bt->data;
}

void SetData(BTreeNode * bt, int data){
    bt->data = data;
}

BTreeNode * GetLeftSubTree(BTreeNode *bt){
    return bt->left;
}

BTreeNode * GetRightSubTree(BTreeNode *bt){
    return bt->right;
}

void MakeLeftSubTree(BTreeNode * main, BTreeNode * sub){
    if(main->left != NULL){
        free(main->left);
    }
    main->left = sub;
}

void MakeRightSubTree(BTreeNode * main, BTreeNode * sub){
    if(main->right != NULL){
        free(main->right);
    }
    main->right = sub;
}

int main(void){
    BTreeNode * bt1 = MakeTreeNode();
    BTreeNode * bt2 = MakeTreeNode();
    BTreeNode * bt3 = MakeTreeNode();
    BTreeNode * bt4 = MakeTreeNode();

    SetData(bt1 , 1);
    SetData(bt2 , 2);
    SetData(bt3 , 3);
    SetData(bt4 , 4);

    MakeLeftSubTree(bt1,bt2);
    MakeRightSubTree(bt1,bt3);
    MakeLeftSubTree(bt2,bt4);

    printf("%d \n", GetData(GetLeftSubTree(bt1)));
    printf("%d \n", GetData(GetLeftSubTree(GetLeftSubTree(bt1))));
}