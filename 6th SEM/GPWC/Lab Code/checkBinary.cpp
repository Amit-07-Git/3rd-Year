#include <iostream>
using namespace std;
class Binary {
private:
    string num;
public:
    void input() {
        cout << "Enter a number: ";
        cin >> num;
    }
    int isBinary() {
        for (int i = 0; i < num.length(); i++) {
            if (num[i] != '0' && num[i] != '1') {
                return 0;
            }
        }
        return 1;
    }
    void onesComplement() {
        if (isBinary() == 0) {
            cout << "Not a binary number";
            return;
        }
        cout << "1's Complement: ";
        for (int i = 0; i < num.length(); i++) {
            if (num[i] == '0')
                cout << '1';
            else
                cout << '0';
        }
    }
};
int main() {
    Binary obj;
    obj.input();
    obj.onesComplement();
    return 0;
}
