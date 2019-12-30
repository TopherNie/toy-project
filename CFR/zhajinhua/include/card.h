//
// Created by Administrator on 2019/12/25 0025.
//

#ifndef TOY_PROJECT_CARD_H
#define TOY_PROJECT_CARD_H

#include <string>
#include <vector>
#include <map>

#define RANK_NUM 10
#define SUIT_NUM 3
#define CARD_NUM RANK_NUM * SUIT_NUM
#define STD_HAND_NUM 3
#define HAND_NUM 4
#define PRIVATE_NUM 2


#define SINGLE 1
#define PAIR 2
#define STRAIGHT 3
#define FLUSH 4
#define FLUSH_STRAIGHT 5
#define LEOPARD 6

using namespace std;

extern const string CARD_SUITS[];
extern const string CARD_RANKS[];
extern const int CARD_RANK_SIZE;

extern map<int, string> TYPE_MAP;

vector<string> dealCards(string &priCard1, string &priCard2);

void analyzeCards(const vector<string>& cards, int &type, int &maxRank);

void compare(const vector<string>& p1Cards, const vector<string>& p2Cards, int &winner, int &type);

#endif //TOY_PROJECT_CARD_H
