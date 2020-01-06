//
// Created by Administrator on 2019/12/25 0025.
//

#ifndef TOY_PROJECT_CARD_H
#define TOY_PROJECT_CARD_H

#include <string>
#include <vector>
#include <map>
#include "player.h"

#define PRE_FLOP 0
#define FLOP 1
#define TURN 2

#define BASIC_BET 1

#define RANK_NUM 10
#define SUIT_NUM 3
#define CARD_NUM RANK_NUM * SUIT_NUM
#define STD_HAND_NUM 3
#define HAND_NUM 4
#define HOLE_NUM 2

#define SINGLE 1
#define PAIR 2
#define STRAIGHT 3
#define FLUSH 4
#define FLUSH_STRAIGHT 5
#define LEOPARD 6

using namespace std;

extern const string CARD_SUITS;
extern const string CARD_RANKS;

extern map<int, string> TYPE_MAP;

void initCards(vector<string> &cardList);

void dealHoleCards(vector<string> &allCards, vector<Player *> &players);

void dealPublicCard(vector<string> &allCards, vector<string> &boardCards);

void analyzeCards(const vector<string>& cards, int &type, int &maxRank);

vector<Player*>  findWinnerByCard(const vector<Player*> &playerList, vector<string> boardCards);

Player* compareCards(Player* p0, Player* p1);

#endif //TOY_PROJECT_CARD_H
