//
// Created by Administrator on 2019/12/30 0030.
//

#ifndef TOY_PROJECT_TREE_H
#define TOY_PROJECT_TREE_H

#include <vector>
#include <string>
#include <array>

using namespace std;

struct Node
{
    int nodeType;
    int currentPlayer;
    int street;
    vector<string> boardCards;
    vector<int> bets;
    bool isTerminal;
    int depth;
    int pot;
};


#endif //TOY_PROJECT_TREE_H
