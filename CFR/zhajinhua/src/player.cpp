//
// Created by Administrator on 2019/12/30 0030.
//

#include <iostream>
#include <player.h>
#include <string>
#include <algorithm>
#include <cmath>
#include <tools.h>

using namespace std;

const array<double, 3> BET_RATE = {0.5, 1.0, 1.5};

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

Action* Player::play(Node* node)
{
    const array<int, 3> betSizes{0};
    transform(BET_RATE.begin(), BET_RATE.end(), betSizes.begin(), [node](double x) { return round(x * node->pot);});
    cout << "Please input your action: " << "( Raise bets: " << arrayToString(betSizes, "|") << " )";
    string actionStr;
    cin >> actionStr;
    auto* action = new Action;
    string type;
    type = actionStr.substr(0, 1);
    action->type = type;
    if (type == RAISE)
    {
        if (actionStr.length() == 2)
        {
            int bets = actionStr[1] - '0';
            if (find(betSizes.begin(), betSizes.end(), bets) == betSizes.end())
            {
                cout << "The bet size should be one of the options provided above!" << endl;
                bets = 0;
            }
            action->bets = bets;
        }
    }
    return action;
}

bool Player::operator==(Player *player)
{
    return this->id == player->id;
}