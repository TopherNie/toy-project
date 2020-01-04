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
    Player* startPlayer;
    Player* currentPlayer;
    vector<Player*> playerList;
    vector<string> cards;
    int lastUserBet;

    int addPlayer(Player* player);
    int nextRoundStartPlayer();
    int nextPlayer();

    int preFlop();
    int settle(Player* winner);
    int battle();
    int clear();
    
};

#endif //TOY_PROJECT_ROUND_H
