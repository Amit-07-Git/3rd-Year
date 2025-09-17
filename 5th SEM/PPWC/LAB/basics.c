#include<stdio.h>
int main(){
  int a = 10;
  char b = 'a'; // printf("%d\n", b); -> Ascii Value
  float c = 6.9f;
  double d = 88;
  printf("Hello World \n");
  printf("%d\n", a);
  printf("%c\n", b);
  printf("%f\n", c);
  printf("%lf\n", d);
  return 0;
}

// ./a.out
/* gcc filename.c -o outputfilename
  ./outputfilename
*/
