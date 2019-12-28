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


#define SINGLE 0
#define PAIR 1
#define STRAIGHT 2
#define FLUSH 3
#define FLUSH_STRAIGHT 4
#define LEOPARD 5

using namespace std;

const string CARD_SUITS[]  = {"s", "h", "c"};
const string CARD_RANKS[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

extern map<int, string> TYPE_MAP;

vector<string> dealCards(string &priCard1, string &priCard2);

void analyzeCards(const vector<string>& cards, int &type, int &maxRank);

#endif //TOY_PROJECT_CARD_H
