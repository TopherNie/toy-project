//
// Created by Administrator on 2019/12/30 0030.
//

#ifndef TOY_PROJECT_ROUND_H
#define TOY_PROJECT_ROUND_H

#include <vector>
#include <string>

#include <player.h>
#include <card.h>

using namespace std;

struct Round
{
    int serial;
    int pot;
    int currentStreet;
    int currentPlayer;
    vector<Player*> playerList;
    vector<string> cards;

    int addPlayer(Player* player);

    int preFlop();
    int battle();
    int clear();
    
};

#endif //TOY_PROJECT_ROUND_H
