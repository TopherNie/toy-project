//
// Created by Administrator on 2019/12/25 0025.
//

#include <random>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include <set>

#define STD_HAND_NUM 5

#define HIGH_CARD 0
#define PAIR 1
#define TWO_PAIR 2
#define THREE_OF_A_KIND 3
#define STRAIGHT 4
#define FLUSH 5
#define FULL_HOUSE 6
#define FOUR_OF_A_KIND 7
#define STRAIGHT_FLUSH 8

using namespace std;

const string CARD_SUITS = "shcd";
const string CARD_RANKS = "23456789TJQKA";
const int ACE_RANK = CARD_RANKS.find('A');
const int ACE_LOW_RANK = -1;

const map<int, string> TYPE_MAP = {
        {HIGH_CARD, "HighCard"},
        {PAIR, "Pair"},
        {TWO_PAIR, "TwoPair"},
        {THREE_OF_A_KIND, "ThreeOfAKind"},
        {STRAIGHT, "Straight"},
        {FLUSH, "Flush"},
        {FULL_HOUSE, "FullHouse"},
        {FOUR_OF_A_KIND, "FourOfAKind"},
        {STRAIGHT_FLUSH, "StraightFlush"},
};

struct CardsRes{
    vector<string> cards;
    int cardsType{};
    vector<int> winRanks;
    vector<int> winCardIndexes;
};

string char2String(char c)
{
    ostringstream oStr;
    oStr << c;
    return oStr.str();
}

int card2Rank(const string &card)
{
    return CARD_RANKS.find(card[0]);
}

char card2Suit(const string &card)
{
    return card[1];
}

template <typename T>
map<T, int> countVecEle(const vector<T> &list){
    map<T, int> resMap;
    for (auto ele : list)
    {
        if (!resMap.count(ele)){
            resMap[ele] = 1;
        } else{
            resMap[ele] += 1;
        }
    }
    return resMap;
}


template <class K, class V>
struct CmpByValue {
    bool operator()(const pair<K, V> &p1, const pair<K, V> &p2) {
        return p1.second == p2.second ? p1.first > p2.first : p1.second > p2.second;
    }
};


template <typename K, typename V>
vector<pair<K, V>> sortMapByValue(const map<K, V> &m, bool reverse)
{
    vector<pair<K, V>> vec(m.begin(), m.end());
    if (reverse){
        sort(vec.begin(), vec.end(), CmpByValue<K, V>());
    } else{
        sort(vec.rbegin(), vec.rend(), CmpByValue<K, V>());
    }
    return vec;
}

template <typename T>
string vecToString(const vector<T>& vec, const string& separator="-")
{
    string res;
    ostringstream oss;
    if (!vec.empty())
    {
        for (auto &ele: vec)
        {
            oss.str("");
            oss << ele;
            res.append(oss.str()).append(separator);
        }
        res.erase(res.size() - 1);
    }
    return res;
}

template <typename T>
int compareEleOneByOne(const vector<T> &vec0, const vector<T> &vec1)
{
    int size0 = vec0.size();
    int size1 = vec1.size();
    int size = min(size0, size1);
    for (int i = 0; i < size;  i++)
    {
        if (vec0.at(i) > vec1.at(i))
        {
            return 1;
        } else if (vec0.at(i) < vec1.at(i)){
            return -1;
        }
    }
    return 0;
}

vector<string> initCards(vector<string> excludeVec)
{
    vector<string> cardList;
    for (char s : CARD_SUITS)
    {
        for (char r : CARD_RANKS)
        {
            string card;
            card.append(char2String(r)).append(char2String(s));
            if (!excludeVec.empty() && find(excludeVec.begin(), excludeVec.end(), card) == excludeVec.end())
            {
                cardList.push_back(card);
            }
        }
    }
    return cardList;
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

void hotEncoding(const vector<int>& indexes, vector<int> &encodingIndexes)
{
    for (auto &i: indexes)
    {
        encodingIndexes[i] = 1;
    }
}

// For all types except Straight and Straight-flush.
void setWinCardIndexes(const vector<string>& cards, const vector<int> &rSortedCardRanks,
                       const vector<pair<int, int>> &rSortedRankCounts, char flushSuit, vector<int> &winRanks, vector<int> &winCardIndexes)
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
        rankSize = rSortedRankCounts.size();
        for (int i = 0; i < rankSize; i ++)
        {
            r = rSortedRankCounts.at(i).first;
            card = char2String(CARD_RANKS[r]);
            int rCount = getCountFromPairs(rSortedRankCounts, r);
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
            // Special case: Four of a kind
            if (i == 0 && winCardIndexes.size() == STD_HAND_NUM - 1)
            {
                int rSortedRankSize = rSortedCardRanks.size();
                for (int j = 0; j < rSortedRankSize; j ++)
                {
                    if (rSortedCardRanks.at(j) != r)
                    {
                        cardIndex = getCardIndex(cards, char2String(CARD_RANKS[rSortedCardRanks.at(j)]), 0);
                        if (cardIndex != -1)
                        {
                            winCardIndexes.push_back(cardIndex);
                            if (find(winRanks.begin(), winRanks.end(), r) == winRanks.end())
                            {
                                winRanks.push_back(r);
                            }
                        }
                        return;
                    }
                }
            }
        }
    }
}

// For Straight and Straight-flush
void analyzeStraight(const vector<string> &cards, const vector<int> &rSortedCardRanks, char flushSuit, bool &result, vector<int> &winRanks, vector<int> &winCardIndexes)
{
    int rankSize = rSortedCardRanks.size();
    if (rankSize >= STD_HAND_NUM)
    {
        vector<int> new_rSortedCardRanks;
        new_rSortedCardRanks.insert(new_rSortedCardRanks.end(), rSortedCardRanks.begin(), rSortedCardRanks.end());
        // Consider the Straight: A2345
        if (find(new_rSortedCardRanks.begin(), new_rSortedCardRanks.end(), ACE_RANK) != new_rSortedCardRanks.end())
        {
            new_rSortedCardRanks.push_back(ACE_LOW_RANK);
            rankSize ++;
        }
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
                // Consider the Straight: A2345
                int tempRank;
                int rank;
                for (unsigned int k = i; k < i + STD_HAND_NUM; k ++)
                {
                    tempRank = new_rSortedCardRanks.at(k);
                    rank = tempRank;
                    // Consider the Straight: A2345
                    if (tempRank == ACE_LOW_RANK)
                    {
                        rank = ACE_RANK;
                    }
                    card = char2String(CARD_RANKS[rank]);
                    if (flushSuit)
                    {
                        card.append(char2String(flushSuit));
                    }
                    cardIndex = getCardIndex(cards, card, 0);
                    if (cardIndex != -1)
                    {
                        winCardIndexes.push_back(cardIndex);
                        if (find(winRanks.begin(), winRanks.end(), tempRank) == winRanks.end())
                        {
                            winRanks.push_back(tempRank);
                        }
                    }
                }
                result = true;
                break;
            }
        }
    }
}


void analyzeCards(const vector<string>& cards, int &type, vector<int> &winRanks, vector<int> &winCardIndexes)
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

    // Four of a kind
    if (rSortedRankCounts.at(0).second == 4)
    {
        type = FOUR_OF_A_KIND;
        setWinCardIndexes(cards, rSortedCardRanks, rSortedRankCounts, false, winRanks,  winCardIndexes);
        return;
    }

    // Full house
    if (rSortedRankCounts.at(0).second == 3 && rSortedRankCounts.size() > 1 && rSortedRankCounts.at(1).second >= 2)
    {
        type = FULL_HOUSE;
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
        // Straight flush
        vector<int> ranksOfSuit = getRanksOfSuit(cards, flushSuit);
        sort(ranksOfSuit.rbegin(), ranksOfSuit.rend());
        analyzeStraight(cards, ranksOfSuit, flushSuit, straight, winRanks, winCardIndexes);
        if (straight)
        {
            type = STRAIGHT_FLUSH;
            return;
        }

        // Only flush
        type = FLUSH;
        setWinCardIndexes(cards, ranksOfSuit, rSortedRankCounts, flushSuit, winRanks, winCardIndexes);
        return;
    }

    // Only straight
    analyzeStraight(cards, rSortedCardRanks, 0, straight, winRanks, winCardIndexes);
    if (straight)
    {
        type = STRAIGHT;
        return;
    }

    // Other types
    setWinCardIndexes(cards, rSortedCardRanks, rSortedRankCounts, false, winRanks, winCardIndexes);

    // Three of a kind
    if (rSortedRankCounts.at(0).second >= 3)
    {
        type = THREE_OF_A_KIND;
        return;
    }

    // Two Pair
    if (rSortedRankCounts.at(0).second == 2 && rSortedRankCounts.size() > 1 && rSortedRankCounts.at(1).second == 2)
    {
        type = TWO_PAIR;
        return;
    }

    // Pair
    if (rSortedRankCounts.at(0).second == 2)
    {
        type = PAIR;
        return;
    }

    // Single
    type = HIGH_CARD;
}

void hotEncodingWinCardIndexes(const vector<string> &cards, int& type, vector<int> &winRanks, vector<int> &winCardEncoding)
{
    vector<int> winCardIndexes;
    analyzeCards(cards, type, winRanks, winCardIndexes);
    hotEncoding(winCardIndexes, winCardEncoding);
}

CardsRes* compareCards(CardsRes* res0, CardsRes* res1)
{
    analyzeCards(res0->cards, res0->cardsType, res0->winRanks, res0->winCardIndexes);
    analyzeCards(res1->cards, res1->cardsType, res1->winRanks, res1->winCardIndexes);
    if (res0->cardsType == res1->cardsType)
    {
        int compRes = compareEleOneByOne(res0->winRanks, res1->winRanks);
        if (compRes == 0)
        {
            // Draw
            return nullptr;
        } else if (compRes > 0){
            return res0;
        }
        return res1;
    } else if (res0->cardsType > res1->cardsType){
        return res0;
    }
    return res1;
}


