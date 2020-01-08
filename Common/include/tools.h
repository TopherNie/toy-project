//
// Created by Administrator on 2019/12/15 0015.
//

#ifndef TOY_PROJECT_TOOLS_H
#define TOY_PROJECT_TOOLS_H

#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <array>
#include <template_func.cpp>

using namespace std;

int getRandom(int n);

string oriArrToStr(double *arr, int size);

string char2String(char c);

string vecToString(const vector<int> &vec, const string& separator="-");

string vecToString(const vector<string>& vec, const string& separator="-");

#endif //TOY_PROJECT_TOOLS_H
