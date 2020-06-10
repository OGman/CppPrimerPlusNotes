#include <iostream>

#include "Sales_item.h"

using namespace std;
int main()
{
    Sales_item item1, item2;
    cout << "type in two Sales_items" << endl;
    while(cin >> item1)
    {
        cout << item1 << endl;
    }
    return 0;
}
