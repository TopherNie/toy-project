//
// Created by Administrator on 2019/12/20 0020.
//

#include <string>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <array>

using namespace std;

void testIteratorForTemplate(array<double, 3> arr)
{
    for (auto &d: arr)
    {
        cout << d << endl;
    }
}

int main()
{
    array<double, 3> arr = {0.5, 1.0, 1.5};
    testIteratorForTemplate(arr);
}