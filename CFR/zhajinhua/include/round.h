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

class Round
{
public:
    int serial{};
    int pot{};
    Player* startPlayer = nullptr;
    Player* currentPlayer = nullptr;
    vector<Player*> playerList;
    vector<string> allCards;
    vector<string> boardCards;
    int lastBet{};
    int roundNum = 1;
    //<street: <playerId: action>>
    map<int, vector<pair<int, Action*>>> streetActionMap;

    void addPlayer(Player* player);
    void nextRoundStartPlayer();
    Player* getNextPlayer();
    void nextPlayer();

    void prepare();
    void settle();
    void battle();
    void clear();
    void run();
    vector<Player*> inPlayers();
    int inPlayerNum();

    State* buildState(int currentStreet);
    
};

#endif //TOY_PROJECT_ROUND_H
