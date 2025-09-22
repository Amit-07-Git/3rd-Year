#include<stdio.h>
int add(int a , int b);
int main(){
  int a, b;
  printf("Enter a and b: ");
  scanf("%d %d",&a,&b);
  int c = add(a,b);
  printf("Sum %d\n",c);
  return 0;
}
int add(int a , int b){
  return a+b;
}
