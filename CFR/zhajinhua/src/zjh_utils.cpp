//
// Created by Administrator on 2020/1/21 0021.
//

#include <vector>
#include <string>
#include <cmath>
#include <constants.h>

using namespace std;

vector<int> getBetSizeVec(int playerRoundBets, int pot, int streetLastBet)
{
    vector<int> betSizeVec;
    if (playerRoundBets >= MAX_BET)
    {
        return betSizeVec;
    }
    for (auto & rate: BET_RATE)
    {
        int bet = (int)round(rate * pot);
        if (bet <= streetLastBet)
        {
            continue;
        }
        if(bet + playerRoundBets > MAX_BET)
        {
            bet = MAX_BET - playerRoundBets;
        }
        if (bet > 0)
        {
            betSizeVec.push_back(bet);
        }
    }
    return betSizeVec;
}

vector<string> getBetSizeStrVec(int playerRoundBets, int pot, int streetLastBet)
{
    vector<string> betSizeStrVec;
    if (playerRoundBets >= MAX_BET)
    {
        return betSizeStrVec;
    }
    for (auto & rate: BET_RATE)
    {
        int bet = (int)round(rate * pot);
        if (bet <= streetLastBet )
        {
            continue;
        }
        if(bet + playerRoundBets > MAX_BET)
        {
            bet = MAX_BET - playerRoundBets;
        }
        if (bet > 0)
        {
            betSizeStrVec.push_back(to_string(bet));
        }
    }
    return betSizeStrVec;
}

