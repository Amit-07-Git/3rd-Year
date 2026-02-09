#include <iostream>
using namespace std;
int main() {
    string s = "aaabbccc";
    int len = s.length();
    for (int i = 0; i < len; i++) {
        int count = 1;
        while (i + 1 < len && s[i] == s[i + 1]) {
            count++;
            i++;
        }
        cout << s[i] << count << "\n";
    }
    return 0;
}
