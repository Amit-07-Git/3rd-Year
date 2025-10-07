#include<stdio.h>
int main(){
  int n;
  printf("Enter the operation number:\n");
  printf("1. Find Factorial:\n");
  printf("2. Check Prime:\n");
  printf("3. Find sum of digits:\n");
  printf("4. Exit:\n");
  scanf("%d",&n);
  switch (n){
    case 1:
        int fact = 1,num,k;
        printf("Enter a number to find Factorial:");
        scanf("%d",&num);
        k = num;
        loopstart1:
          if(num>0){
            fact = fact*num;
            num = num - 1;
            goto loopstart1;
          }
          printf("Factorial of %d is %d\n",k,fact);
      break;
    case 2:
        int m,i=2,count=1;
        printf("Enter a number to check prime:");
        scanf("%d",&m);
        loopstart2:
            if (i<=m/2){
              if (m%i==0){
                count=0;
                goto check;
              }
              i++;
              goto loopstart2;
            }
            check:
            if(count){
              printf("Prime");
            } else{
              printf("Not Prime");
            }
          break;
    case 3:
        int n , sum = 0, rem;
        printf("Enter a number:");
        scanf("%d", &n);
        loopstart3:
          if(n>0){
            rem = n%10;
            sum = sum+rem;
            n = n/10;
            goto loopstart3;
          }
          printf("The sum of the digits is %d\n",sum);
      break;
    case 4:
      printf("Exit\n");
      break;
  default:
    printf("Invalid Input\n");
  }
}
