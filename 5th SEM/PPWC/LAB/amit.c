#include<stdio.h>
int main(){
  float start, end, cost=0.35;
  printf("Mielage Reimbusment calculator: \n");
  printf("Enter beginning odometer reading: ");
  scanf("%f",&start);
  printf("Enter ending odometer reading: ");
  scanf("%f",&end);
  printf("You travelled at %.1f miles at %.2f per mile\n",(end-start),cost);
  printf("Your reimbusment is $%.1f\n",((end-start)*cost));
  return 0;
}
