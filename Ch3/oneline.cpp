#include <iostream>
#include <string>

using std::string;
using std::cin;
using std::cout;
using std::endl;
int main()
{
    string s;
    getline(cin, s);
    cout << s << endl;
    cin >> s;
    cout << s <<endl;
    return 0;
}
