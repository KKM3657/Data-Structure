#include <stdio.h>
#include <stdlib.h>
typedef int element;
int size, i = 0;

//시간복잡도가 n*log(n)인 병합 정렬
void MergeTwoArea(int arr[], int left, int mid, int right){
    int fIdx = left;
    int rIdx = mid + 1;
    int i;

    int * sortArr = (int*)malloc(sizeof(int)*(right+1));
    int sIdx = left;

    while(fIdx <= mid && rIdx <= right){
        if(arr[fIdx] <= arr[rIdx]) {
            sortArr[sIdx] = arr[fIdx++];
        } else {
            sortArr[sIdx] = arr[rIdx++];
        }
        sIdx++;
    }

    if(fIdx > mid) {
        for(i= rIdx; i <= right; i++, sIdx++){
            sortArr[sIdx] = arr[i];
        }
    } else {
        for(i =fIdx; i <= mid; i++, sIdx++){
            sortArr[sIdx] = arr[i];
        }
    }
    for(i=left; i <= right; i++){
        arr[i] = sortArr[i];
    }

    free(sortArr);

}

void MergeSort(int arr[], int left, int right){
    int mid;

    if(left< right){
        mid = (left+right) / 2;

        MergeSort(arr, left, mid);
        MergeSort(arr,mid+1, right);

        MergeTwoArea(arr, left, mid, right);
    }
}

//시간복잡도가 n^2인 버블정렬
void BubbleSort(int arr[], int n){
    int i, j;
    int temp;

    for(i=0; i<n-1; i++){
        for(j=0; j<(n-i)-1; j++){
            if(arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    element list1[] = { 69, 10, 30, 2, 16, 8, 31, 22 };
    element list2[] = { 69, 10, 30, 2, 16, 8, 31, 22 };
    size = 8;	// list 배열의 원소 개수

    printf("\n [ 초기 상태 ] \n");
    for (int i = 0; i <= size - 1; i++) printf(" %d", list1[i]);
    printf("\n");

    MergeSort(list1, 0, 7);
    BubbleSort(list2,8);

    printf("\n [ 병합 정렬 상태 ] \n");
    for(i=0; i<size; i++){
        printf(" %d", list1[i]);
    }
    printf("\n");
    
    printf("\n [ 버블 정렬 상태 ] \n");
    for(i=0; i<size; i++){
        printf(" %d", list2[i]);
    }

}