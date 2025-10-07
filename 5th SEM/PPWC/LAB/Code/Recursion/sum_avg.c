#include<stdio.h>
double sum(double a,double b, double c){
  double sum = a + b + c;
  return sum;
}
double avg(double a,double b, double c){
  double avg = (a + b + c)/3;
  return avg;
}
int main(){
  double x = sum(1.1,2.2,3.3);
  double y = avg(1.1,2.2,3.3);
  printf("The sum is %lf and the avg is %lf\n",x,y);
  return 0;
}
