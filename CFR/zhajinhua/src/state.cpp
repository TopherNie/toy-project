//
// Created by Administrator on 2020/1/13 0013.
//

#include <state.h>
#include <tools.h>

string Action::toString()
{
    string res;
    res.append(type).append(to_string(bets));
    return res;
}

ostream& operator<<(ostream & os, const NodeVal* nodeVal)
{
    cout << "{nodeType:" << nodeVal->nodeType
            << ", currentPlayer:" << nodeVal->currentPlayer
            << ", street:" << nodeVal->street
            << ", boardCards:" << vecToString(nodeVal->boardCards)
            << ", bets:" << vecToString(nodeVal->bets)
            << ", isTerminal:" << nodeVal->isTerminal
            << ", depth:" << nodeVal->depth
            << ", pot:" << nodeVal->pot
            << "}";
    return os;
}

