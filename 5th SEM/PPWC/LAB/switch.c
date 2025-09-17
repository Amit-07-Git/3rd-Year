#include<stdio.h>
int main(){
  int a, b;
  char c;
  printf("Enter the values of a: ");
  scanf("%d",&a);
  printf("Enter the values of b: ");
  scanf("%d",&b);
  printf("Enter the operation: ");
  scanf("%c",&c);
  switch(c){
    case '+':
      int sum = a+b;
      printf("The addition is: %d \n",sum);
      break;
    case '-':
      int sub = a-b;
      printf("The subtraction is: %d \n",sub);
      break;
    case '*':
      int mul = a*b;
      printf("The multiplication is: %d \n",mul);
      break;
    case '/':
      int div = a/b;
      printf("The division is: %d \n",div);
      break;
    case '%':
      int mod = a%b;
      printf("The modulo is: %d \n",mod);
      break;
    default:
      printf("Invalid Operation can't perform the task.\n");
  }
  return 0;
}
