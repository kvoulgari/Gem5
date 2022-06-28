

#include <stdio.h>

int calculateDet(int matrix[2][2]){
    int tmp1 = (matrix[0][0]) * (matrix[1][1]);
    int tmp2 = (matrix[1][0]) * (matrix[0][1]);
    return tmp1-tmp2;
    
}

int main()
{
    int matrix[2][2] = {{1,2}, {3,4}};
    int result = calculateDet(matrix);
    printf("Hello World %d",result);

    return 0;
}

