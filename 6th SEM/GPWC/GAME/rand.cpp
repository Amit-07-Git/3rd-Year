#include<iostream>
using namespace std;
int main(){
  srand(10);
  for (int i = 0 ; i<9; i++){
    int a = rand()%10;
    cout <<a << "\n";
  }
  return 0;
}
