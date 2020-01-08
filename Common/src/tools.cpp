//
// Created by Administrator on 2019/12/15 0015.
//

#include <tools.h>
#include <random>
#include <iostream>
#include <algorithm>


using namespace std;

default_random_engine e;

int getRandom(int n)
{
    uniform_int_distribution<int> u(0.0, n);
    return u(e);
}

string oriArrToStr(double *arr, int size)
{
    string res;
    ostringstream oStr;
    if (size > 0){
        oStr.str("");
        for (int i = 0; i < size; i ++)
        {

            if (i == size - 1)
            {
                oStr << arr[i];
            } else{
                oStr << arr[i] << " ";
            }
        }
        return oStr.str();
    }
}

string char2String(char c)
{
    ostringstream oStr;
    oStr << c;
    return oStr.str();
}

string vecToString(const vector<int> &vec, const string& separator) {
    string res;
    if (!vec.empty()) {
        for (auto &ele: vec) {
            res.append(to_string(ele)).append(separator);
        }
        res.erase(res.size() - 1);
    }
    return res;
}

string vecToString(const vector<string>& vec, const string& separator)
{
    string res;
    if (!vec.empty())
    {
        for (auto &ele: vec)
        {
            res.append(ele).append(separator);
        }
        res.erase(res.size() - 1);
    }
    return res;
}



