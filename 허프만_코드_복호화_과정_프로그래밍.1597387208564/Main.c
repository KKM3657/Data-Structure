#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
typedef struct treeNode {	// 연결 자료구조로 구성하기 위해 트리의 노드 정의
    char data;
    struct treeNode *left;  // 왼쪽 서브 트리에 대한 링크 필드
    struct treeNode *right; // 오른쪽 서브 트리에 대한 링크 필드
} treeNode;

// data를 루트 노드로 하여 왼쪽 서브 트리와 오른쪽 서브 트리를 연결하는 연산
treeNode* makeRootNode(char data, treeNode* leftNode, treeNode* rightNode) {
    treeNode* root = (treeNode *)malloc(sizeof(treeNode));
    root->data = data;
    root->left = leftNode;
    root->right = rightNode;
    return root;
}
void dicord_huffman(treeNode *tN, char * result, int *idx, int array[], int len){
    if(*idx>len){
        printf("오류 입니다.");
        exit(-1);
    }
    if(tN->left == NULL && tN->right == NULL){                //해당 노드가 단말노드 일경우 재귀 중지
        *result = tN->data;                                   //데이터 추출
        return;
    }
    if(array[(*idx)++] == 0){
        dicord_huffman(tN->left, result, idx, array, len);         //허프만 부호가 0 일때 왼쪽으로 이동
    }
    else{
        dicord_huffman(tN->right, result, idx, array, len);        //허프만 부호가 1 일때 오른쪽으로 이동
    }
}

int main() {
    // 허프만 코드 이진 트리 만들기
    treeNode* n11 = makeRootNode('u', NULL, NULL);
    treeNode* n10 = makeRootNode('i', NULL, NULL);
    treeNode* n9 = makeRootNode('h', NULL, NULL);
    treeNode* n8 = makeRootNode('5', n10, n11);
    treeNode* n7 = makeRootNode('f', NULL, NULL);
    treeNode* n6 = makeRootNode('s', NULL, NULL);
    treeNode* n5 = makeRootNode('4', n8, n9);
    treeNode* n4 = makeRootNode('n', NULL, NULL);
    treeNode* n3 = makeRootNode('3', n6, n7);
    treeNode* n2 = makeRootNode('2', n4, n5);
    treeNode* n1 = makeRootNode('1', n2, n3);

    // 허프만 zip data
    int huffman_zip[] = { 0,1,1,0,1,0,1,1,1,1,0,0,1,0,0,1,0,1,1,0,1,0,1,0,0 };


    int idx =0;
    char result;
    int len = sizeof(huffman_zip)/sizeof(int);
    char letterArray[len];                                  //결과값을 저장할 문자열 선언
    memset(letterArray, 0, len);                            //배열 초기화

    for(int i =0; idx!= len;i++){                           //복호화 과정 반복
        dicord_huffman(n1,&result,&idx,huffman_zip, len);   //호프만 부호화 코드 복호화 과정
        letterArray[i] = result;                            //결과값 저장
    }
    printf("결과값: %s",letterArray);

    return 0;
}