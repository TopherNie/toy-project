//
// Created by Administrator on 2019/12/25 0025.
//

#include <random>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

#include "card.h"
#include <tools.h>
#include <player.h>

const string CARD_SUITS = "shcd";
const string CARD_RANKS = "01234567";
const unsigned long CARD_NUM = CARD_SUITS.size() * CARD_RANKS.size();

const map<int, string> TYPE_MAP = {
        {TYPE_FOLD, "Fold"},
        {TYPE_OPPONENT_FOLD, "Opponent-Fold"},
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

int getCountFromPairs(const vector<pair<int, int>> &rankCounts, const int rank)
{
    for (auto &rc: rankCounts)
    {
        if (rc.first == rank)
        {
            return rc.second;
        }
    }
    return 0;
}

vector<int> getRanksOfSuit(const vector<string> &cards, char suit)
{
    vector<int> ranksOfSuit;
    for (auto &c: cards)
    {
        if (card2Suit(c) == suit)
        {
            ranksOfSuit.push_back(card2Rank(c));
        }
    }
    return ranksOfSuit;
}

int getCardIndex(const vector<string>& cards, const string &findCard, int i)
{
    int count = 0;
    int len = cards.size();
    for (int j = 0; j < len; j ++)
    {
        string card = cards.at(j);
        if (card.find(findCard) != string::npos)
        {
            if (count == i)
            {
                return j;
            }
            count ++;
        }
    }
    return -1;
}

// For all types except Straight and Straight-flush.
void setWinCardIndexes(const vector<string>& cards, const vector<int> &rSortedCardRanks,
                       const vector<pair<int, int>> &sortedRankCounts, char flushSuit, vector<int> &winRanks, vector<int> &winCardIndexes)
{
    int rankSize;
    string card;
    int cardIndex;
    int r;
    if (flushSuit)
    {
        rankSize = rSortedCardRanks.size();
        for (int i = 0; i < rankSize && winCardIndexes.size() < STD_HAND_NUM; i ++)
        {
            r = rSortedCardRanks.at(i);
            card = char2String(CARD_RANKS[r]);
            card.append(char2String(flushSuit));
            cardIndex = getCardIndex(cards, card, 0);
            if (cardIndex != -1)
            {
                winCardIndexes.push_back(cardIndex);
                if (find(winRanks.begin(), winRanks.end(), r) == winRanks.end())
                {
                    winRanks.push_back(r);
                }
            }
        }
    } else{
        rankSize = sortedRankCounts.size();
        for (int i = 0; i < rankSize; i ++)
        {
            r = sortedRankCounts.at(i).first;
            card = char2String(CARD_RANKS[r]);
            int rCount = getCountFromPairs(sortedRankCounts, r);
            for (int j = 0; j < rCount && winCardIndexes.size() < STD_HAND_NUM; j ++)
            {
                cardIndex = getCardIndex(cards, card, j);
                if (cardIndex != -1)
                {
                    winCardIndexes.push_back(cardIndex);
                    if (find(winRanks.begin(), winRanks.end(), r) == winRanks.end())
                    {
                        winRanks.push_back(r);
                    }
                }
            }
        }
    }
}

// For Straight and Straight-flush
void analyzeStraight(const vector<string> &cards, const vector<int> &rSortedCardRanks, char flushSuit, bool &result, vector<int> &winRanks,  vector<int> &winCardIndexes)
{
    int rankSize = rSortedCardRanks.size();
    if (rankSize >= STD_HAND_NUM)
    {
        vector<int> new_rSortedCardRanks;
        new_rSortedCardRanks.insert(new_rSortedCardRanks.end(), rSortedCardRanks.begin(), rSortedCardRanks.end());
        for (unsigned int i = 0; i <= rankSize - STD_HAND_NUM; i ++)
        {
            unsigned int j = i;
            while(j < i + STD_HAND_NUM - 1)
            {
                if (new_rSortedCardRanks.at(j) - 1 != new_rSortedCardRanks.at(j + 1))
                {
                    break;
                }
                j ++;
            }
            if (j == i + STD_HAND_NUM - 1)
            {
                string card;
                int cardIndex;
                int rank;
                for (unsigned int k = i; k < i + STD_HAND_NUM; k ++)
                {
                    rank = new_rSortedCardRanks.at(k);
                    card = char2String(CARD_RANKS[rank]);
                    if (flushSuit)
                    {
                        card.append(char2String(flushSuit));
                    }
                    cardIndex = getCardIndex(cards, card, 0);
                    if (cardIndex != -1)
                    {
                        winCardIndexes.push_back(cardIndex);
                        if (find(winRanks.begin(), winRanks.end(), rank) == winRanks.end())
                        {
                            winRanks.push_back(rank);
                        }
                    }
                }
                result = true;
                break;
            }
        }
    }
}


void analyzeCards(const vector<string>& cards, int &type, vector<int>& winRanks, vector<int> &winCardIndexes)
{
    unsigned int cardSize = cards.size();
    vector<int> cardRanks(cardSize);
    transform(cards.begin(), cards.end(), cardRanks.begin(), card2Rank);

    map<int, int> rankCounts = countVecEle<int>(cardRanks);
    vector<pair<int, int>> rSortedRankCounts = sortMapByValue(rankCounts, true);

    // Unique
    set<int> cardRankSet(cardRanks.begin(), cardRanks.end());
    // Reverse the order
    vector<int> rSortedCardRanks(cardRankSet.rbegin(), cardRankSet.rend());

    // Leopard
    if (rSortedRankCounts.at(0).second == STD_HAND_NUM)
    {
        type = LEOPARD;
        setWinCardIndexes(cards, rSortedCardRanks, rSortedRankCounts, false, winRanks, winCardIndexes);
        return;
    }

    char flushSuit = 0;
    bool straight = false;

    // Flush
    vector<char> cardSuits(cardSize);
    transform(cards.begin(), cards.end(), cardSuits.begin(), card2Suit);
    map<char, int> suitCounts = countVecEle<char>(cardSuits);
    vector<pair<char, int>> sortedSuitCounts =  sortMapByValue(suitCounts, true);
    if (sortedSuitCounts.at(0).second >= STD_HAND_NUM)
    {
        flushSuit = sortedSuitCounts.at(0).first;
    }


    if (flushSuit)
    {
        vector<int> ranksOfSuit = getRanksOfSuit(cards, flushSuit);
        sort(ranksOfSuit.rbegin(), ranksOfSuit.rend());
        // Straight flush
        analyzeStraight(cards, ranksOfSuit, flushSuit, straight, winRanks, winCardIndexes);
        if (straight)
        {
            type = FLUSH_STRAIGHT;
            return;
        }

        // Only flush
        type = FLUSH;
        setWinCardIndexes(cards, ranksOfSuit, rSortedRankCounts, flushSuit, winRanks, winCardIndexes);
        return;
    }

    // Only straight
    analyzeStraight(cards, rSortedCardRanks, 0, straight,  winRanks, winCardIndexes);
    if (straight)
    {
        type = STRAIGHT;
        return;
    }

    // Other types
    setWinCardIndexes(cards, rSortedCardRanks, rSortedRankCounts, false, winRanks, winCardIndexes);


    // Pair
    if (rSortedRankCounts.at(0).second == 2)
    {
        type = PAIR;
        return;
    }

    // Single
    type = SINGLE;
}


Player* compareCards(Player* p0, Player* p1)
{
    vector<int> p0WinRanks, p1WinRanks;
    analyzeCards(p0->cards, p0->cardsType, p0WinRanks, p0->cardTypeIndexes);
    analyzeCards(p1->cards, p1->cardsType, p1WinRanks, p1->cardTypeIndexes);
    if (p0->cardsType == p1->cardsType)
    {
        int compRes = compareEleOneByOne(p0WinRanks, p1WinRanks);
        if (compRes == 0)
        {
            // Draw
            return nullptr;
        } else if (compRes > 0){
            return p0;
        }
        return p1;
    } else if (p0->cardsType > p1->cardsType){
        return p0;
    }
    return p1;
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




