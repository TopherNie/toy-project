//
// Created by Administrator on 2020/1/13 0013.
//

#ifndef TOY_PROJECT_STATE_H
#define TOY_PROJECT_STATE_H

#include <map>
#include <vector>
#include <iostream>

using namespace std;

class Action
{
public:
    string type;
    int bets{};

    string toString();
};

struct State{
    int pot{};
    int currentStreet{};
    int nextPlayerId{};
    vector<string> boardCards;
    map<int, vector<pair<int, Action*>>> streetActionMap;
};

struct NodeVal{
    string type{};
    int currentPlayerId{};
    int nextPlayerId{};
    int street{};
    vector<string> boardCards;
    int bet{};
    bool isTerminal{};
    int depth{};
    int pot{};

    friend ostream& operator<<(ostream & os,const NodeVal* nodeVal);
};

#endif //TOY_PROJECT_STATE_H
