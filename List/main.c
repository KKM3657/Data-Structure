#include <stdio.h>

#define LEN 8

typedef struct list{
    int ar[LEN];
    int dataNum;
    int curPosition;
}List;

void listClear(List *pList){
    pList->ar[LEN]= 0;
    pList->dataNum = 0;
    pList->curPosition = 0;
}

void listDataAdd(List *pList, int *data){
    pList->ar[pList->curPosition] = *data;
    (pList->dataNum)++;
    (pList->curPosition)++;
}

void listPrint(List *pList){
    if(pList->ar[LEN] == 0){
        printf("공백리스트\n\n");
    } else{
        printf("List ={ ");
        for(int i= 0; i<(pList->dataNum);i++){
            printf("%d ",pList->ar[i]);
        }
        printf("}");
    }
}

void listDataNum(List *pList){
    printf("\n%d개 입니다.\n\n",pList->dataNum);
}

void listInsertData(List *pList, int *data, int *idx){
    int i=0;

    if(*idx > (pList->dataNum)-1) {printf("실패했습니다.");}
    else{
        (pList->dataNum)++;
        (pList->curPosition)++;
        for(i =(pList->curPosition);i>= *idx; i--){
            pList->ar[i]=pList->ar[i-1];
        }
        pList->ar[*idx] = *data;
    }
}

void listEraseData(List *pList, int *idx){
    int i=0;
    if(*idx> (pList->dataNum)-1){ printf("실패했습니다.\n");}
    else{
        for(i=*idx; (i<pList->dataNum-1); i++) {
            pList->ar[i] = pList->ar[i + 1];
        }
        (pList->dataNum)--;
        (pList->curPosition)--;
    }
}

int main(void) {
    List list;
    int data;
    int idx;

    printf("순차 리스트 생성\n");
    listClear(&list);
    listPrint(&list);

    printf("데이터 저장\n");
    for(int i=0; i<5;i++) {
        printf("데이터를 입력하시오:");
        scanf("%d", &data);
        listDataAdd(&list, &data);
    }
    listPrint(&list);
    listDataNum(&list);

    printf("데이터를 입력하시오:");
    scanf("%d", &data);
    printf("삽입할 인덱스를 입력하시오:");
    scanf("%d",&idx);
    listInsertData(&list,&data,&idx);
    listPrint(&list);
    listDataNum(&list);

    printf("데이터 삭제\n");
    printf("삭제할 인덱스를 입력하시오:");
    scanf("%d",&idx);
    listEraseData(&list,&idx);
    listPrint(&list);
    listDataNum(&list);

    return 0;
}
