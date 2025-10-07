#include<stdio.h>
int main(){
  int celsius;
  double fahrenheit;
  printf("Enter the value of Celsius: ");
  scanf("%d", &celsius);
  printf("Celsius to Fahrenheit is \n");
  fahrenheit = (9.0/5 * celsius) + 32;
  printf("%lf\n", fahrenheit);
  return 0;
}
