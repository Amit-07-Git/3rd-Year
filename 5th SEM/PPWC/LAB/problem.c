#include<stdio.h>
int main(){
  int a;
  int b;
  printf("Enter the value of 1st Number: ");
  scanf("%d", &a);
  printf("Enter the value of 2nd Number: ");
  scanf("%d", &b);
  double sum = a+b;
  double sub = a-b;
  double mul = a*b;
  double div = a/b;
  double mod = a%b;
  printf("Addition: %lf\n", sum);
  printf("Substraction: %lf\n", sub);
  printf("Multipliation: %lf\n", mul);
  printf("Division: %lf\n", div);
  printf("Modulus: %lf\n", mod);
  return 0;
}
