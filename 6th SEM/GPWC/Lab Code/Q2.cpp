#include <iostream>
using namespace std;

int main() {
    int num, temp, rem, result = 0;
    cout << "Enter a three-digit integer: ";
    cin >> num;
    temp = num;

    while (temp != 0) {
        remainder = temp % 10;
        result += rem * rem * rem;
        num /= 10;
    }
     
    return 0;
}

