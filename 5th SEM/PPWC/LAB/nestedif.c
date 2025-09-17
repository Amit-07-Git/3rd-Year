//Write a c program to find maximum integer among three input values
#include<stdio.h>
int main(){
  int a,b,c;
  printf("Enter the value of a: ");
  scanf("%d",&a);
  printf("Enter the value of b: ");
  scanf("%d",&b);
  printf("Enter the value of c: ");
  scanf("%d",&c);
  if(a>b){
    if(a>c){
      printf("%d is greatest\n",a);
    }
    else{
      printf("%d is greatest\n",c);
    }
  }
  else{
    if(b>c){
      printf("%d is greatest\n",b);
    }
    else{
      printf("%d is greatest\n",c);
    }
  }
}
