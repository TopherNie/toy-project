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
    vector<string> allCards;
    vector<string> boardCards;
    int lastUserBet;

    int addPlayer(Player* player);
    int nextRoundStartPlayer();
    int nextPlayer();

    int preFlop();
    int settle();
    int battle();
    int clear();
    vector<Player*> inPlayers();
    int inPlayerNum();
    
};

#endif //TOY_PROJECT_ROUND_H
