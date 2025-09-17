// Write a c program that takes 3 integer value as length of a triangle side and determine the type of triangle
#include<stdio.h>
int main(){
  int a,b,c;
  printf("Enter the value of a: ");
  scanf("%d",&a);
  printf("Enter the value of b: ");
  scanf("%d",&b);
  printf("Enter the value of c: ");
  scanf("%d",&c);
  if (a+b<=c || b+c<=a || a+c<=b){
    printf("Invalid triangle\n");
  } else if(a==b && a==c){
    printf("Its an equilateral triangle\n");
  } else if(a==b || a==c || b==c){
    printf("Its a Isosceles triangle\n");
  } else {
    printf("Its a Scalene triangle\n");
  }
}
