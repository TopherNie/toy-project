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
    int serial{};
    int pot{};
    Player* startPlayer;
    Player* currentPlayer;
    vector<Player*> playerList;
    vector<string> allCards;
    vector<string> boardCards;
    int lastBet{};
    int roundNum = 1;
    //<street: <playerId: action>>
    vector<pair<int, vector<pair<int, Action*>>>> streetActions;

    void addPlayer(Player* player);
    void nextRoundStartPlayer();
    void nextPlayer();

    void prepare();
    void settle();
    void battle();
    void clear();
    void run();
    vector<Player*> inPlayers();
    int inPlayerNum();

    Node* buildNode();
    
};

#endif //TOY_PROJECT_ROUND_H
