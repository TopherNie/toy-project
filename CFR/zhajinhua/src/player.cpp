//
// Created by Administrator on 2019/12/30 0030.
//

#include <iostream>
#include <player.h>
#include <string>

using namespace std;

int Player::roundBets()
{
    int res = 0;
    if (!history.empty())
    {
        for (auto &action: history)
        {
            res += action->bets;
        }
    }
    return res;
}

Action* Player::play()
{
    string actionStr;
    cout << "Please input your action: ";
    cin >> actionStr;
    auto* action = new Action;
    char type = actionStr[0];
    action->type = type;
    if (type == RAISE)
    {
        action->bets = actionStr[1] - '0';
    }
    return action;
}

bool Player::operator==(Player *player)
{
    return this->id == player->id;
}