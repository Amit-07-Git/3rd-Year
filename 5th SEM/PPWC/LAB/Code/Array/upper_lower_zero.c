#include<stdio.h>
int main() {
    int row, col;

    printf("Enter the no of rows for matrix: ");
    scanf("%d", &row);
    printf("Enter the no of columns for matrix: ");
    scanf("%d", &col);
    int matrix[row][col];

    printf("Enter elements for matrix:");
    for(int i = 0; i < row; i++) {
      for(int j = 0; j < col; j++) {
          printf("Element [%d][%d]:", i, j);
          scanf("%d", &matrix[i][j]);
        }
    }
    int upper = 0;
    int lower = 0;
    int zero = 0;
    for(int i = 0; i < row; i++) {
      for(int j = 0; j < col; j++) {
        if(i>j){
          matrix[i][j] == 0;
          upper = 1;
        }
        else if(i<j){
          matrix[i][j] == 0;
          lower = 1;          
        }
        else{
          matrix[i][j] == 0;
          zero = 1;
        }
      
    }
  }
    if(upper == 1)
      printf("Upper");
    else if(lower == 1)
      printf("Lower");
    else if(zero == 1)
      printf("Zero");
  return 0;
}
