#include<stdio.h>

int main() {
    int row1, col1, row2, col2;

    printf("Enter the no of rows for matrix 1: ");
    scanf("%d", &row1);
    printf("Enter the no of columns for matrix 1: ");
    scanf("%d", &col1);
    int matrix1[row1][col1];

    printf("Enter elements for matrix 1:");
    for(int i = 0; i < row1; i++) {
      for(int j = 0; j < col1; j++) {
          printf("Element [%d][%d]:", i, j);
          scanf("%d", &matrix1[i][j]);
        }
    }

    printf("Enter the no of rows for matrix 2: ");
    scanf("%d", &row2);
    printf("Enter the no of columns for matrix 2: ");
    scanf("%d", &col2);
    int matrix2[row2][col2]; 

    printf("Enter elements for matrix 2:");
    for(int i = 0; i < row2; i++) {
      for(int j = 0; j < col2; j++) {
          printf("Element [%d][%d]:", i, j);
          scanf("%d", &matrix2[i][j]);
        }
    }

    if (col1 != row2)
        printf("Multiplication is not possible");
    else {
      int matrix3[row1][col2];   
      for(int i = 0; i < row1; i++) {
        for(int j = 0; j < col2; j++) {
          matrix3[i][j] = 0;
          for(int k = 0; k < col1; k++) { 
            matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
          }
        } 
      }
    printf("Multiplied matrix:\n");
      for(int i = 0; i < row1; i++) {
        for(int j = 0; j < col2; j++) {
            printf("%d ", matrix3[i][j]); 
        }
        printf("\n");
      }
    }
    return 0;
}
