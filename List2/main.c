#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

#define TRUE 1
#define FALSE 0

#define LIST_LEN 100
typedef int LData;

typedef struct __ArrayList
{
    LData arr[LIST_LEN];
    int dataNumber;
    int curPosition;
}ArrayList;

typedef  ArrayList List;

void ListInit(List * plist);
void LInsert(List * plist, LData data);

int LFirst(List *plist, LData *pdata);
int LNext(List *plist, LData *pdata);

LData LRemove(List * plist);
int LCount(List * plist);

#endif
#include <stdio.h>

void ListInit(List * plist){
    (plist->dataNumber)=0;
    (plist->curPosition)=-1;
}

void LInsert(List *plist, LData data){
    if(plist-> dataNumber >= LIST_LEN){
        puts("저장이 불가능합니다.");
        return;
    }

    plist->arr[plist->dataNumber] = data;
    (plist->dataNumber)++;
}

int LFirst(List *plist, LData *pdata){
    if(plist->dataNumber ==0){
        return FALSE;
    }

    (plist->curPosition) =0;
    *pdata = plist->arr[0];
    return TRUE;

}

int LNext(List *plist, LData *pdata){
    if(plist->curPosition >= (plist->dataNumber)-1){
        return FALSE;
    }
    (plist->curPosition)++;
    *pdata= plist->arr[plist->curPosition];
    return TRUE;
}

LData LRemove(List *plist){
    int rpos = plist->curPosition;
    int num = plist->dataNumber;
    int i;

    LData rdata = plist->arr[rpos];

    for(i= rpos; i<num-1; i++){
        plist->arr[i] = plist->arr[i+1];
    }
    (plist->curPosition)--;
    (plist->dataNumber)--;
    return rdata;
}

int LCount(List *plist){
    return plist->dataNumber;
}

int main(void){
    //ArrayList 생성 및 초기화
    List list;
    int data;
    ListInit(&list);

    //5개의 데이터 저장
    LInsert(&list, 11);
    LInsert(&list, 11);
    LInsert(&list, 22);
    LInsert(&list, 22);
    LInsert(&list, 33);

    //저장된 데이터의 전체 출력
    printf("현재 데이터의 수: %d \n",LCount(&list));
    if(LFirst(&list,&data)){
        printf("%d ", data);

        while(LNext(&list, &data)) {
            printf("%d ", data);
        }
    }
    printf("\n\n");

    //숫자 22를 탐색하여 모두 삭제

    if(LFirst(&list, &data)){
        if(data == 22) {
            LRemove(&list);
        }
        while (LNext(&list, &data)) {
            if(data == 22) {
                LRemove(&list);
            }
        }
    }

    //삭제 후 남은 데이터 전체 출력
    printf("현재 데이터의 수: %d \n", LCount(&list));

    if(LFirst(&list, &data)){
        printf("%d ", data);

        while(LNext(&list,&data))
            printf("%d ", data);
    }
    printf("\n\n");
    return 0;
}