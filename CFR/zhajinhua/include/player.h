//
// Created by Administrator on 2019/12/28 0028.
//

#ifndef TOY_PROJECT_PLAYER_H
#define TOY_PROJECT_PLAYER_H

#include <vector>
#include <string>

#define PLAYER_1 1
#define PLAYER_2 2

using namespace std;

struct Player
{
    int id;
    vector<string> cards;
    int totalBets;
    int totalChips;

    void act(int bets);
};

#endif //TOY_PROJECT_PLAYER_H
