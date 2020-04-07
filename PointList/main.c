#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

#define TRUE 1
#define FALSE 0

#define LIST_LEN 100
typedef struct _point{
    int xpos;
    int ypos;
}Point;

typedef Point * LData;

typedef struct __ArrayList
{
    LData arr[LIST_LEN];
    int dataNumber;
    int curPosition;
}ArrayList;
void SetPointPos(Point *ppos, int xpos, int ypos);
void ShowPointPos(Point *ppos);
int PointComp(Point *pos1, Point *pos2);

typedef  ArrayList List;

void ListInit(List * plist);
void LInsert(List * plist, LData data);

int LFirst(List *plist, LData *pdata);
int LNext(List *plist, LData *pdata);

LData LRemove(List * plist);
int LCount(List * plist);

#endif


#include <stdio.h>
#include <stdlib.h>
void SetPointPos(Point *ppos, int xpos, int ypos){
    ppos->xpos= xpos;
    ppos->ypos= ypos;
}
void ShowPointPos(Point *ppos){
    printf("[%d,%d]",ppos->xpos,ppos->ypos);
}
int PointComp(Point *pos1, Point *pos2){
    if(pos1->xpos == pos2->xpos){
        if(pos1->ypos == pos2->ypos){
            return 0;
        }
        else { return 1;}
    }
    else{
        if(pos1->ypos == pos2->ypos){
            return 2;
        }
        else { return -1;}
    }
}

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
    Point compPos;
    Point * ppos;

    ListInit(&list);

    //4개의 데이터 저장
   ppos = (Point *)malloc(sizeof(Point));
   SetPointPos(ppos, 2, 1);
   LInsert(&list, ppos);

    ppos = (Point *)malloc(sizeof(Point));
    SetPointPos(ppos, 2, 2);
    LInsert(&list, ppos);

    ppos = (Point *)malloc(sizeof(Point));
    SetPointPos(ppos, 3, 1);
    LInsert(&list, ppos);

    ppos = (Point *)malloc(sizeof(Point));
    SetPointPos(ppos, 3, 2);
    LInsert(&list, ppos);

    //저장된 데이터의 전체 출력
    printf("현재 데이터의 수: %d \n",LCount(&list));
    if(LFirst(&list,&ppos)){
        ShowPointPos(ppos);

        while(LNext(&list, &ppos)) {
            ShowPointPos(ppos);
        }
    }
    printf("\n\n");

    //xpos가 2인 모든 데이터 삭제
    compPos.xpos=2;
    compPos.ypos=0;

    if(LFirst(&list, &ppos)){
        if(PointComp(ppos, &compPos)==1) {
            ppos=LRemove(&list);
            free(ppos);
        }
        while (LNext(&list, &ppos)) {
            if(PointComp(ppos, &compPos)==1) {
                ppos=LRemove(&list);
                free(ppos);
            }
        }
    }

    //삭제 후 남은 데이터 전체 출력
    printf("현재 데이터의 수: %d \n", LCount(&list));

    if(LFirst(&list, &ppos)){
        ShowPointPos(ppos);

        while(LNext(&list,&ppos))
            ShowPointPos(ppos);
    }
    printf("\n\n");
    return 0;
}