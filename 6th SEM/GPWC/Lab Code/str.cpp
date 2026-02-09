#include <iostream>
#include <string>
#include <sstream>
using namespace std;
int main(){
  //char hi[6] = {'H','e','l','l','o','\0'};
  //string s = "hello";
  //char s1[10] = "hello";
  //char s2[10] = "world";
  //char s3[10];
  //strcpy(s3,s2);
  //int len = strlen(s1);
  
  string s1;
  cout << "Enter ur name: ";
  //cin >> s1; 
  getline(cin,s1);
  //int len = s1.compare(s2);
  
  cout << "Greetings " << s1 << "\n";
  
  return 0;
}    
