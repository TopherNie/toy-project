//
// Created by Administrator on 2019/12/25 0025.
//

#ifndef TOY_PROJECT_CARD_H
#define TOY_PROJECT_CARD_H

#include <string>
#include <vector>
#include <map>
#include "player.h"

using namespace std;

extern const string CARD_SUITS;
extern const string CARD_RANKS;
extern const unsigned long CARD_NUM;

extern const map<int, string> TYPE_MAP;
extern const map<int, string> STREET_MAP;

void initCards(vector<string> &cardList);

void dealHoleCards(vector<string> &allCards, vector<Player *> &players);

void dealPublicCard(vector<string> &allCards, vector<string> &boardCards);

void analyzeCards(const vector<string>& cards, int &type, vector<int>& winRanks, vector<int> &winCardIndexes);

vector<Player*>  findWinnerByCard(const vector<Player*> &playerList, vector<string> boardCards);

Player* compareCards(Player* p0, Player* p1);

#endif //TOY_PROJECT_CARD_H
