//
// Created by Administrator on 2019/12/30 0030.
//

#include <iostream>
#include <player.h>
#include <string>

using namespace std;

string Player::play()
{
    string action;
    cout << "Please input your action: ";
    cin >> action;
    return action;
}