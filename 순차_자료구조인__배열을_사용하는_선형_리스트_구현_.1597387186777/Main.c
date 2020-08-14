/* 프로그램 작성에 사용한 header file(*.h) 내용을 
   현 위치에 주석처리하여 제출바랍니다. */

/*
//
// Created by mmm36 on 2020-03-27.
//

#ifndef LINKEDLIST_ARRAY_LINKEDLIST_ADT_H
#define LINKEDLIST_ARRAY_LINKEDLIST_ADT_H

int* listMake(int* p, int *size) {										//배열 생성 및 동적할당 생성 함수

    printf("배열의 크기를 입력하시오: ");
    scanf("%d", size);

    p = (int*)malloc((*size) * sizeof(int));					//동적할당

    if (p == NULL) {
        printf("동적할당 오류!");
    }

    printf("배열의 값을 입력하시오: ");										//배열의 값 입력
    for (int i = 0; i < *size; i++) {
        int input = 0;
        scanf("%d", &input);
        p[i] = input;
    }
    for (int i = 0; i < *size; i++) {
        printf("%d ", p[i]);
    }
    return p;
}

void listErase(int* a) {															//동적할당 제거 함수
    printf("\n배열을 삭제합니다.");
    free(a);
}

void list_IdxAdd(int* p, int *size) {									//원소 삽입 함수
    int number = 0;
    int idx = 0;

    realloc(p, (*size + 1) * sizeof(int));						//추가 할당

    printf("\n삽입할 인덱스를 입력하시오: ");
    scanf("%d", &idx);

   
    while (idx > *size) {
        printf("인덱스 입력 오류!\n");
        printf("삽입할 인덱스를 입력하시오: ");
        scanf("%d", &idx);
    }

    printf("값을 입력하시오: ");
    scanf("%d", &number);
    printf("\n");

    for (int i = *size; i > idx; i--) {
        p[i] = p[i - 1];
    }
    p[idx] = number;
    (*size)++;
    for (int i = 0; i < *size; i++) {
        printf("%d ", p[i]);
    }
}

void list_IdxErase(int* p, int *size) {							//인덱스 원소 삭제
    int number = 0;
    int idx = 0;

    printf("\n삭제할 인덱스를 입력하시오: ");
    scanf("%d", &idx);

    
    while (idx > *size+1) {
        printf("인덱스 입력 오류!");
        printf("\n삽입할 인덱스를 입력하시오: ");
        scanf("%d", &idx);
    }

    for (int i = idx; i < *size; i++) {
        p[i] = p[i+1];
    }
    (*size)--;
    for (int i = 0; i < *size; i++) {
        printf("%d ", p[i]);
    }
    realloc(p, (*size) * sizeof(int));
}

#endif //LINKEDLIST_ARRAY_LINKEDLIST_ADT_H

*/


#include <stdio.h>
#include <stdlib.h>
#include "LINKEDLIST_ARRAY.h"

int main(void) {
	int size = 0;
	int* p = NULL;
	p=listMake(p, &size);
	list_IdxAdd(p, &size);
	list_IdxErase(p, &size);
	listErase(p);
	return 0;
}