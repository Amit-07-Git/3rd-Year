#include<stdio.h>
int main(){
  int bill,unit;
  printf("Enter the number of units consumed: ");
  scanf("%d",&unit);
  if(unit<=100){
    bill = unit*5;
    printf("Total cost = %d\n",bill);
  }
  else if(unit<=200){
    bill = (unit-100)*7+100*7;
    printf("Total cost = %d\n",bill);
  }
  else{
    bill = (unit-200)*10+100*7+100*5;
    printf("Total cost = %d\n",bill);
  }
  return 0;
}
