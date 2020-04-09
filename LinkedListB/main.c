#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    int data;
    struct _node *next;
}Node;

int main(void){
    Node * head =NULL;
    Node * tail =NULL;
    Node * cur = NULL;

    Node * newNode = NULL;
    Node * DMY = NULL;
    int readData;

    DMY= (Node*)malloc(sizeof(Node));
    DMY->next =NULL;
    head = DMY;
    //데이터를 입력받는 과정
    while(1){
        printf("자연수를 입력하시오:");
        scanf("%d", &readData);
        if(readData <1){
            break;
        }

        //노드 추가 과정
        newNode = (Node*)malloc(sizeof(Node));
        newNode->data = readData;
        newNode->next = NULL;

        if(DMY->next == NULL){
            DMY->next = newNode;
        } else{
            tail->next = newNode;
        }
        tail = newNode;
    }
    printf("\n");

    //입력받은 데이터의 출력 과정

    printf("입력 받은 데이터의 전체출력!\n");
    if(DMY->next == NULL){
        printf("저장된 자연수가 존재하지 않습니다. \n");
    }
    else
    {
        cur=DMY->next;
        printf("%d", cur->data);

        while(cur->next != NULL){
            cur = cur->next;
            printf("%d", cur->data);
        }
    }
    printf("\n\n");

    //메모리 해제 과정
    if(head == NULL){
        return 0;
    }
    else{
        Node *delNode = DMY;
        Node *delNextNode = DMY->next;

        while(delNode != tail){
            delNode->next=delNextNode->next;
            printf("%d를 삭제합니다. \n", delNextNode->data);
            free(delNextNode);
            delNextNode=delNode->next;
        }
    }
    return 0;
}
