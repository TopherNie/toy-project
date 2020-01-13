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

bool Player::operator==(Player *player)
{
    return this->id == player->id;
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

Action* Player::play(const State* state)
{
    cout << "Your hole cards: " << vecToString(cards) << " || Board: " << vecToString(state->boardCards)
         << " || Your round bets: " << getRoundBets() << " || Pot: " << state->pot << " || Your chips: " << totalChips << endl;
    auto* action = new Action;
    array<string, 3> betSizeStrArr;
    transform(BET_RATE.begin(), BET_RATE.end(), betSizeStrArr.begin(), [state](double x) { return to_string((int)round(x * state->pot));});
    cout << "Please input your action" << "( Raise bets: " << arrayToString(betSizeStrArr) << " ): ";
    string actionStr;
    cin >> actionStr;
    string type;
    int strLen = actionStr.size();
    if (strLen > 0)
    {
        type = actionStr.substr(0, 1);
        action->type = type;
        if (type == RAISE)
        {
            if (strLen >= 2)
            {
                string betsStr = actionStr.substr(1, strLen - 1);
                if (find(betSizeStrArr.begin(), betSizeStrArr.end(), betsStr) != betSizeStrArr.end())
                {
                    action->bets = stoi(betsStr);
                } else{
                    cout << "The bet size should be one of the options provided above!" << endl;
                }
            }
        }
    }
    return action;
}

void Player::confirmToContinue()
{
    cout << "Input anything to continue:" << endl;
    string inputStr;
    cin >> inputStr;
}
