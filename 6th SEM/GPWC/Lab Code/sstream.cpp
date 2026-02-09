#include <iostream>
#include <string>
#include <sstream>
using namespace std;
int main(){
  string s1 = "hello";
  stringstream obj(s1);
  string newstr;
  while(obj >> newstr){
    cout << newstr << "";
  }
  
  return 0;
}    
