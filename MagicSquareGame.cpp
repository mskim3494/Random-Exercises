// 마방진 게임 만들기

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <tgmath.h>


int menu()
{
    printf(" -----------------------\n");
    printf("        <<마방진>>\n");
    printf(" -----------------------\n");
    printf("    1) 숫자 입력\n");
    printf("    2) 게임 종료\n");
    printf(" -----------------------\n");
    printf("메뉴 선택 =>");
    
    int Select;
    scanf("%d", &Select);
    
    return Select;
}

int digitNum(int x)
{
    int count = 0;
    while(x >= 1){
        x /= 10;
        count++;
    }
    return count;
}

void magicSquare (int n)
{
    unsigned m[n][n];
    int x, y, cx, cy, i, j, total, count;
    
    memset(m, 0, sizeof(unsigned)*n*n);
    
    x = 0;
    n%2 == 0 ? y = (n/2)-1 : y = (n/2);
    count = 1;
    m[x][y] = count++;
    total = n * n;
    
    for(i=0; i<total-1; i++){
        (x-1) < 0 ? cx = n-1 : cx = x-1;
        (y-1) < 0 ? cy = n-1 : cy = y-1;
        
        if(m[cx][cy] != 0) {
            x = x+1;
            m[x][y] = count++;
        } else {
            x = cx;
            y = cy;
            m[x][y] = count++;
        }
    }
    
    int k, tmp = 0;
    count = 0; // number of digits in the largest int

    count = digitNum(total);
    
    // print the matrix
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            printf(" [");
            tmp = digitNum(m[i][j]);
            for(k=0; k<(count - tmp); k++){
                printf(" ");
            }
            printf("%d]", m[i][j]);
        }
        printf("\n");
    }
    
    int acc1, acc2, acc3;
    acc1 = acc2 = acc3 = 0;
    
    for(i=0; i<n; i++){
        acc1 += m[i][i];
        acc2 += m[0][i];
        acc3 += m[i][0];
    }
    if(acc1==acc2 && acc1 == acc3){
        printf("일열 합계: %d\n", acc1);
    }
}

int main()
{
    int Select;
    int size;
    
    while (1){
        Select = menu();
        if(Select == 1){
            printf("매트릭스 크기: ");
            scanf("%d", &size);
            magicSquare(size);
        } else if (Select == 2){
            break;
        } else {
            printf("다시 입력 해 주세요\n");
        }
    }
    return 0;
}