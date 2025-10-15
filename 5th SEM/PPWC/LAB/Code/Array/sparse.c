#include<stdio.h>
int main(){
  int row,col,total;
  printf("Enter the no of rows:");
  scanf("%d",&row);
  printf("Enter the no of columns:");
  scanf("%d",&col);
  total = row*col;
  int matrix[row][col];
  int count=0;
  for(int i = 0; i<row; i++){
    for(int j = 0; j<col; j++){
      printf("Element [%d][%d]:",i,j);
      scanf("%d",&matrix[i][j]);
    }
  }
  for(int i = 0; i < row; i++) {
    for(int j = 0; j < col; j++) {
      if(matrix[i][j] == 0)
        count++;
    }
  }
    if(count >= total/2)
      printf("Its a sparse matrix\n");
    else
      printf("Its not a sparse matrix\n");
  return 0;
}
