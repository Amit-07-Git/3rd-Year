#include <iostream>
using namespace std;
struct student {
    char name[100];
    int rollno;
};
int main() {
    student s1;
    char Name[] = "Ram Kumar";
    cout << "Enter student name: ";
    cout << "Enter roll number: ";
    cin >> s.rollno;
    if (strcmp(s1.name, Name) == 0) {
        cout << "matched" << endl;
    } else {
        cout << "not matched" << endl;
    }
    return 0;
}    
