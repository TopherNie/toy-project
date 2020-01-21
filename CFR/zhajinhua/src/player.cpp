//
// Created by Administrator on 2019/12/30 0030.
//

#include <iostream>
#include <player.h>
#include <string>
#include <algorithm>
#include <cmath>
#include <tools.h>
#include <zjh_utils.h>

using namespace std;

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
    int roundBets = getRoundBets();
    cout << "Your hole cards: " << vecToString(cards) << " || Board: " << vecToString(state->boardCards)
         << " || Your round bet: " << roundBets << " || Pot: " << state->pot << " || Your chips: " << totalChips << endl;
    auto* action = new Action;
    vector<string> betSizeStrVec = getBetSizeStrVec(roundBets, state->pot, state->streetLastBet);
    cout << "Please input your action" << "( Raise bet: " << vecToString(betSizeStrVec) << " ): ";
    string actionStr;
    cin >> actionStr;
    int strLen = actionStr.size();
    if (strLen > 0)
    {
        action->type = actionStr.substr(0, 1);
        if (action->type == ALL_IN)
        {
            action->bets = MAX_BET - roundBets;
        }
        if (action->type == RAISE)
        {
            if (strLen >= 2)
            {
                string betsStr = actionStr.substr(1, strLen - 1);
                if (find(betSizeStrVec.begin(), betSizeStrVec.end(), betsStr) != betSizeStrVec.end())
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
