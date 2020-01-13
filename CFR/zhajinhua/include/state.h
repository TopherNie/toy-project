//
// Created by Administrator on 2020/1/13 0013.
//

#ifndef TOY_PROJECT_STATE_H
#define TOY_PROJECT_STATE_H

#include <map>
#include <vector>

using namespace std;

struct Action
{
    string type;
    int bets{};

    string toString();
};

struct State{
    int pot;
    int currentStreet;
    vector<string> boardCards;
    map<int, vector<pair<int, Action*>>> streetActionMap;
};

#endif //TOY_PROJECT_STATE_H
