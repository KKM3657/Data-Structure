#include <stdio.h>
typedef int element;
int size, i = 0;

// 주어진 부분집합 안에서 피봇의 위치를 확정하여 분할 위치를 정하는 연산
int partition(element a[], int begin, int end, int Select) {
    int  pivot, L, R, t;
    pivot = -1;
    element temp;
    L = begin;
    R = end;

    switch(Select){
        case 1:
            pivot = begin;                      //처음에 위치한 원소를 피봇 원소로 선택
            break;
        case 2:
            pivot = (int)((begin + end) / 2.0);	//중간에 위치한 원소를 피봇 원소로 선택
            break;
        case 3:
            pivot = end;                        //끝에 위치한 원소를 피봇 원소로 선택
            break;
        default:
            Select = (Select % 3 + 1);
    }

    printf("\n [%d단계 : pivot=%d ] \n", ++i, a[pivot]);
    while (L<R) {
        while ((a[L]<a[pivot]) && (L<R)) L++;
        while ((a[R] >= a[pivot]) && (L<R)) R--;
        if (L<R) {					// L과 R 원소의 자리 교환
            temp = a[L];
            a[L] = a[R];
            a[R] = temp;

            if (L == pivot)			// L이 피봇인 경우,
                pivot = R;			// 변경된 피봇의 위치(R)를 저장!
        } // if(L<R)
    } // while(L<R)

    // (L=R)이 된 경우,
    // 더 이상 진행할 수 없으므로 R 원소와 피봇 원소의 자리를 교환하여 마무리
    temp = a[pivot];
    a[pivot] = a[R];
    a[R] = temp;
    for (t = 0; t<size; t++) printf(" %d", a[t]);	// 현재의 정렬 상태 출력
    printf("\n");
    return R;	// 정렬되어 확정된 피봇의 위치 반환


}

void quickSort(element a[], int begin, int end, int Select) {
    int p;
    if (begin<end) {
        p = partition(a, begin, end, Select);	// 피봇의 위치에 의해 분할 위치 결정
        quickSort(a, begin, p - 1, Select);		// 피봇의 왼쪽 부분집합에 대해 퀵 정렬을 재귀호출
        quickSort(a, p + 1, end, Select);		// 피봇의 오른쪽 부분집합에 대해 퀵 정렬을 재귀호출
    }
}

int main() {
    element list[8] = { 69, 10, 30, 2, 16, 8, 31, 22 };
    size = 8;	// list 배열의 원소 개수
    int input;
    printf("\n [ 초기 상태 ] \n");
    for (int i = 0; i <= size - 1; i++) printf(" %d", list[i]);
    printf("\n");

    printf("Pivot 위치를 입력하시오:");
    scanf(" %d", &input);

    if(input == 1)
        quickSort(list, 0, size - 1,1);
    else if(input == 2)
        quickSort(list, 0, size - 1,2);
    else if(input == 3)
        quickSort(list, 0, size - 1,3);
    else
        printf("오류");

    getchar();
}