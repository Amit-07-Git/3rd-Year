//write a c program to assign a grade 
#include<stdio.h>
int main(){
  int marks;
  printf("Enter a Marks: ");
  scanf("%d",&marks);
  if(marks>90){
    printf("O Grade\n");
  }else if(marks>=80){
    printf("A Grade\n");
  }else if(marks>=70){
    printf("B Grade\n");
  }else if(marks>=60){
    printf("C Grade\n");
  }else if(marks>50){
    printf("D Grade\n");
  }else{
    printf("F Grade\n");
  }
  return 0;
}
