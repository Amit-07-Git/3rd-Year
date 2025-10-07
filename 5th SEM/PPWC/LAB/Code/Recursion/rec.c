#include<stdio.h>
int multiply(int m, int n){
  int ans;
  if(n==1)
    ans=m;
  else
    ans = m+multiply(m,n-1);
}
int main(){
  int c;
  c = multiply(6,3);
  printf("%d\n",c);
  return 0;
}
