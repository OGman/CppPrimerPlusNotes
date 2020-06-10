#include <string>
#include <iostream>

using namespace std;

int main() {
    string s;
    cin >> s;
    string newstr;
    for (auto c:s) {
        if (!ispunct(c)) {
            newstr += c;
        }
    }
    cout << newstr << endl;
    return 0;
}
