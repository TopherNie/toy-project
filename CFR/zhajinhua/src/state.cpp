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
    cout << "{type:" << nodeVal->type
            << ", currentPlayerId:" << nodeVal->currentPlayerId
            << ", street:" << nodeVal->street
            << ", boardCards:" << vecToString(nodeVal->boardCards)
            << ", bet:" << nodeVal->bet
            << ", isTerminal:" << nodeVal->isTerminal
            << ", depth:" << nodeVal->depth
            << ", pot:" << nodeVal->pot
            << "}";
    return os;
}
