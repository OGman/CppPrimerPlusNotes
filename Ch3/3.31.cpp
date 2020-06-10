#include <iostream>

using namespace std;

int main() {
    int a[10] = {0};
    for (int i = 0; i < 10; ++i) {
        a[i] = i;
    }

    cout << "{";
    for (auto v : a) {
        cout << v << " ";
    }
    cout << "}" << endl;
    return 0;
}
