//
// Created by Administrator on 2019/12/25 0025.
//

#include <random>
#include <vector>
#include <map>
#include <algorithm>

#include "card.h"
#include <tools.h>

const string CARD_SUITS[] = {"s", "h", "c", "d"};
const string CARD_RANKS[] = {"0", "1", "2", "3", "4", "5", "6"};

const int CARD_RANK_SIZE = sizeof(CARD_RANKS) / sizeof(string);

map<int, string> TYPE_MAP = {
        {SINGLE, "Single"},
        {PAIR, "Pair"},
        {STRAIGHT, "Straight"},
        {FLUSH, "Flush"},
        {FLUSH_STRAIGHT, "Flush-Straight"},
        {LEOPARD, "Leopard"}
};

vector<string> dealCards(string &priCard1, string &priCard2)
{
    vector<string> remainCards;
    for (const string& suit: CARD_SUITS)
    {
        for (const auto & r : CARD_RANKS)
        {
            string card = r + suit;
            remainCards.push_back(card);
        }
    }
    shuffle(remainCards.begin(), remainCards.end(), mt19937(random_device()()));
    int size = remainCards.size();
    priCard1 = remainCards.at(size - 1);
    remainCards.pop_back();
    priCard2 = remainCards.at(size - 2);
    remainCards.pop_back();
    return remainCards;
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

void compare(const vector<string>& p1Cards, const vector<string>& p2Cards, int &winner, int &type)
{
    int p1Type{}, p2Type{};
    int p1MaxRank{}, p2MaxRank{};
    analyzeCards(p1Cards, p1Type, p1MaxRank);
    analyzeCards(p2Cards, p2Type, p2MaxRank);
    if (p1Type == p2Type)
    {
        if (p1MaxRank == p2MaxRank)
        {
            // Draw
            type = p1Type;
            winner = 0;
        } else if (p1MaxRank > p2MaxRank){
            type = p1Type;
            winner = 1;
        } else{
            type = p2Type;
            winner = 2;
        }

    } else if (p1Type > p2Type){
        type = p1Type;
        winner = 1;
    } else{
        type = p2Type;
        winner = 2;
    }
}





