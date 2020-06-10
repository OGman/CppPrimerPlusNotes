#include <string>
#include <iostream>

using namespace std;

int main()
{
    string s1;
    string s2;
    cin >> s1 >> s2;
    if(s1 != s2)
    {
        if(s1 > s2)
        {
            cout << s1 << endl;
        } else
        {
            cout << s2 << endl;
        }
         
    }
    return 0;
}
