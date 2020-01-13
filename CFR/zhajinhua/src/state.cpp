//
// Created by Administrator on 2020/1/13 0013.
//

#include <state.h>

string Action::toString()
{
    string res;
    res.append(type).append(to_string(bets));
    return res;
}

