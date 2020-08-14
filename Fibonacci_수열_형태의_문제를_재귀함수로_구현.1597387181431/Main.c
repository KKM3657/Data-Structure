#include <stdio.h>
int main(void) {
    int input1, input2;
    int n;
    int result;

    printf("F(1)를 입력하시오:");
    scanf("%d", &input1);              //F(1)입력받음
    printf("F(2)를 입력하시오:");
    scanf("%d", &input2);               //F(2)입력받음
    printf("n을 입력하시오:");
    scanf("%d", &n);                    //n입력받음

    if (n < 3) {
        printf("오류 입니다. 다시 입력하시오\n");
        printf("n을 입력하시오:");
        scanf("%d", &n);                    //n입력받음
    }

    //반복문을 통한 F(i)=F(i-1)+F(i-2) 값 구하기
    for (int count = 3; count <= n; count++) {            //초기값 F(1)와 F(2)을 제외한 입력받은 n만큼 반복
        result = input1 + input2;                            //F(i)=F(i-1)+F(i-2)
        input1 = input2;                                     //F(i-2)값 재설정
        input2 = result;                                      //F(i-1)값 재설정
    }

    printf("F(n)은 %d입니다.", result);
    return 0;

}