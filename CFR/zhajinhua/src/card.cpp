//
// Created by Administrator on 2019/12/25 0025.
//

#include <random>
#include <vector>
#include <map>
#include <algorithm>

#include "card.h"
#include <tools.h>
#include <player.h>

const string CARD_SUITS[] = {"s", "h", "c", "d"};
const string CARD_RANKS[] = {"0", "1", "2", "3", "4", "5", "6"};

map<int, string> TYPE_MAP = {
        {SINGLE, "Single"},
        {PAIR, "Pair"},
        {STRAIGHT, "Straight"},
        {FLUSH, "Flush"},
        {FLUSH_STRAIGHT, "Flush-Straight"},
        {LEOPARD, "Leopard"}
};

void initCards(vector<string> &cardList)
{
    if (cardList.size() != CARD_NUM)
    {
        cardList.clear();
        for (const string& suit: CARD_SUITS)
        {
            for (const auto & r : CARD_RANKS)
            {
                string card = r + suit;
                cardList.push_back(card);
            }
        }
    }
    shuffle(cardList.begin(), cardList.end(), mt19937(random_device()()));
}

void dealCards(vector<string> &cards, vector<Player *> &players, int street)
{
    // The number of cards dealt to per player.
    int numPer = 1;
    if (street == PRE_FLOP)
    {
        numPer = 2;
    }
    for (auto &p: players)
    {
        for (int i = 0; i < numPer; i++)
        {
            p -> cards.push_back(cards.at(cards.size() - 1));
            cards.pop_back();
        }
    }
}

int card2Rank(const string &card)
{
    return card[0] - '0';
}

char card2Suit(const string &card)
{
    return card[1];
}

void analyzeCards(const vector<string>& cards, int &type, int &maxRank)
{
    const int cardSize = cards.size();
    vector<int> cardRanks(cardSize);
    transform(cards.begin(), cards.end(), cardRanks.begin(), card2Rank);
    map<int, int> rankCounts = countVecEle<int>(cardRanks);
//    printMap(rankCounts);
    vector<pair<int, int>> sortedRankCounts =  sortMapByValue(rankCounts, true);
//    printPairVector(sortedCounts);
    const pair<int, int> maxCardCount = sortedRankCounts.at(0);
    maxRank = maxCardCount.first;

    // Leopard
    if (maxCardCount.second >= 3)
    {
        type = LEOPARD;
        return;
    }

    // Flush
    bool flush = false;
    vector<char> cardSuits(cardSize);
    transform(cards.begin(), cards.end(), cardSuits.begin(), card2Suit);
    map<char, int> suitCounts = countVecEle<char>(cardSuits);
    vector<pair<char, int>> sortedSuitCounts =  sortMapByValue(suitCounts, true);
    if (sortedSuitCounts.at(0).second >= 3)
    {
        flush = true;
    }

    // Straight
    bool straight = false;
    int rankSize = rankCounts.size();
    if (rankSize >= 3)
    {
        // The map has been sorted by key automatically.
        vector<pair<int, int>> rankPairs(rankCounts.begin(), rankCounts.end());
        for (int i = 0; i <= rankSize - STD_HAND_NUM; i ++)
        {
            int sFirst = rankPairs.at(i).first;
            int sSecond = rankPairs.at(i + 1).first;
            int sThird = rankPairs.at(i + 2).first;
            if (sFirst + 1 == sSecond && sSecond + 1 == sThird)
            {
                straight = true;
                maxRank = sThird;
                break;
            }

        }
    }

    //Flush-straight
    if (straight && flush)
    {
        type = FLUSH_STRAIGHT;
        return;
    }

    // Only flush
    if (!straight && flush)
    {
        type = FLUSH;
        return;
    }

    // Only straight
    if (straight && !flush)
    {
        type = STRAIGHT;
        return;
    }

    // Pair
    if (maxCardCount.second == 2)
    {
        type = PAIR;
        return;
    }

    // Single
    type = SINGLE;

}

void compare(const vector<string>& p0Cards, const vector<string>& p1Cards, int &winner, int &type)
{
    int p0Type{}, p1Type{};
    int p0MaxRank{}, p1MaxRank{};
    analyzeCards(p0Cards, p0Type, p0MaxRank);
    analyzeCards(p1Cards, p1Type, p1MaxRank);
    if (p0Type == p1Type)
    {
        if (p0MaxRank == p1MaxRank)
        {
            // Draw
            type = p0Type;
            winner = 0;
        } else if (p0MaxRank > p1MaxRank){
            type = p0Type;
            winner = PLAYER_0;
        } else{
            type = p1Type;
            winner = PLAYER_1;
        }

    } else if (p0Type > p1Type){
        type = p0Type;
        winner = PLAYER_0;
    } else{
        type = p1Type;
        winner = PLAYER_1;
    }
}





