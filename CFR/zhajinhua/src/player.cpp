//
// Created by Administrator on 2019/12/30 0030.
//

#include <iostream>
#include <player.h>
#include <string>

using namespace std;


string Action::toString()
{
    string res;
    res.append(type).append(to_string(bets));
    return res;
}

bool Player::isRobot()
{
    return false;
}

int Player::getRoundBets()
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

Action* Player::getLastAction()
{
    return history.at(history.size() - 1);
}

Action* Player::play()
{
    string actionStr;
    cout << "Please input your action: ";
    cin >> actionStr;
    auto* action = new Action;
    string type;
    type = actionStr.substr(0, 1);
    action->type = type;
    if (type == RAISE)
    {
        if (actionStr.length() == 2)
        {
            action->bets = actionStr[1] - '0';
        }
    }
    return action;
}

bool Player::operator==(Player *player)
{
    return this->id == player->id;
}