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

const string CARD_SUITS = "shc";
const string CARD_RANKS = "0123456";

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
        for (char s : CARD_SUITS)
        {
            for (char r : CARD_RANKS)
            {
                string card;
                card.append(char2String(r)).append(char2String(s));
                cardList.push_back(card);
            }
        }
    }
    shuffle(cardList.begin(), cardList.end(), mt19937(random_device()()));
}

void dealHoleCards(vector<string> &allCards, vector<Player *> &players)
{
    for (auto &p: players)
    {
        for (int i = 0; i < HOLE_NUM; i++)
        {
            p->cards.push_back(allCards.at(allCards.size() - 1));
            allCards.pop_back();
        }
    }
}

void dealPublicCard(vector<string> &allCards, vector<string> &boardCards)
{
    boardCards.push_back(allCards.at(allCards.size() - 1));
    allCards.pop_back();
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
    unsigned int cardSize = cards.size();
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
        vector<pair<int, int>> rankPairs(rankCounts.rbegin(), rankCounts.rend());
        for (unsigned int i = 0; i <= rankSize - STD_HAND_NUM; i ++)
        {
            int sFirst = rankPairs.at(i).first;
            int sSecond = rankPairs.at(i + 1).first;
            int sThird = rankPairs.at(i + 2).first;
            if (sFirst - 1 == sSecond && sSecond - 1 == sThird)
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

vector<Player*> findWinnerByCard(const vector<Player*> &playerList, vector<string> boardCards)
{
    // Initialize it as Draw
    vector<Player*> winnerList;
    for (auto &p: playerList)
    {
        if (!p->isOut)
        {
            p->cards.insert(p->cards.end(), boardCards.begin(), boardCards.end());
            if (winnerList.empty())
            {
                winnerList.push_back(p);
                continue;
            }
            Player* tempWinner = compareCards(winnerList.at(0), p);
            // Draw
            if (tempWinner == nullptr)
            {
                winnerList.push_back(p);
                continue;
            }
            // New winner
            if (tempWinner != winnerList.at(0))
            {
                winnerList.clear();
                winnerList.push_back(p);
            }
        }
    }
    return winnerList;
}


Player* compareCards(Player* p0, Player* p1)
{
    int p0MaxRank, p1MaxRank;
    analyzeCards(p0->cards, p0->cardsType, p0MaxRank);
    analyzeCards(p1->cards, p1->cardsType, p1MaxRank);
    if (p0->cardsType == p1->cardsType)
    {
        if (p0MaxRank == p1MaxRank)
        {
            // Draw
            return nullptr;
        } else if (p0MaxRank > p1MaxRank){
            return p0;
        }
        return p1;
    } else if (p0->cardsType > p1->cardsType){
        return p0;
    }
    return p1;
}





