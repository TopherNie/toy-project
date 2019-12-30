//
// Created by Administrator on 2019/12/30 0030.
//

#ifndef TOY_PROJECT_TREE_H
#define TOY_PROJECT_TREE_H

#include <vector>
#include <string>

using namespace std;

struct Node
{
    int nodeType;
    int currentPlayer;
    int street;
    vector<string> board;
    vector<string> bets;
    bool isTerminal;
    int depth;
    int pot;
    vector<vector<double>> strategy;
};

struct Tree
{
    Node* root;
};

#endif //TOY_PROJECT_TREE_H
