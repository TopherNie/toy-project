//
// Created by Administrator on 2020/1/13 0013.
//

#ifndef TOY_PROJECT_STATE_H
#define TOY_PROJECT_STATE_H

#include <map>
#include <vector>
#include <iostream>
#include <constants.h>

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
    int streetLastBet{};
    vector<int> inPlayerIDs;
    vector<string> boardCards;
    map<int, vector<pair<int, Action*>>> streetActionMap;
};

struct PlayerNodeInfo{
    int playerID;
    bool isOut;
    int roundBet;
};

struct NodeVal{
    int type{};
    int currentPlayerId{};
    int street = PRE_FLOP;
    vector<string> boardCards;
    int bet{};
    bool isTerminal{};
    bool isTransitional{};
    int depth{};
    int pot = 3 * BASIC_BET;
    vector<PlayerNodeInfo*> playerNodeInfoVec;

    friend ostream& operator<<(ostream & os,const NodeVal* nodeVal);
};

#endif //TOY_PROJECT_STATE_H
