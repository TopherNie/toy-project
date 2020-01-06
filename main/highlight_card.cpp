//
// Created by Administrator on 2019/12/25 0025.
//

#include <random>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <iostream>

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

map<int, string> TYPE_MAP = {
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
vector<pair<K, V>> sortMapByValue(map<K, V> &m, bool reverse)
{
    vector<pair<K, V>> vec(m.begin(), m.end());
    if (reverse){
        sort(vec.begin(), vec.end(), CmpByValue<K, V>());
    } else{
        sort(vec.rbegin(), vec.rend(), CmpByValue<K, V>());
    }
    return vec;
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

vector<int> hotEncodingCardIndex(const vector<string>& cards, vector<pair<int, int>> &rankPairs,
        vector<pair<int, int>> &sortedRankCounts, char flushSuit, bool isStraight)
{
    vector<int> res;
    for (auto &rp: rankPairs)
    {
        if (flushSuit)
        {

        }
    }
}

vector<int> hotEncoding(vector<int>& indexes, const int len)
{
    vector<int> res(len);
    for (auto &i: indexes)
    {
        res[i] = 1;
    }
    return res;
}

void analyzeCards(const vector<string>& cards, int &type, vector<int> &cardEncoding)
{
    unsigned int cardSize = cards.size();
    vector<int> cardRanks(cardSize);
    transform(cards.begin(), cards.end(), cardRanks.begin(), card2Rank);
    map<int, int> rankCounts = countVecEle<int>(cardRanks);

    vector<pair<int, int>> sortedRankCounts = sortMapByValue(rankCounts, true);

    // Four of a kind
    if (sortedRankCounts.at(0).second == 4)
    {
        type = FOUR_OF_A_KIND;
        return;
    }

    // Full house
    if (sortedRankCounts.at(0).second == 3 && sortedRankCounts.size() > 1 && sortedRankCounts.at(1).second >= 2)
    {
        type = FULL_HOUSE;
        return;
    }

    // The map "rankCounts" has been sorted by key automatically.
    // Reverse the order
    vector<pair<int, int>> rankPairs(rankCounts.rbegin(), rankCounts.rend());

    // Flush
    bool flush = false;
    vector<char> cardSuits(cardSize);
    transform(cards.begin(), cards.end(), cardSuits.begin(), card2Suit);
    map<char, int> suitCounts = countVecEle<char>(cardSuits);
    vector<pair<char, int>> sortedSuitCounts =  sortMapByValue(suitCounts, true);
    if (sortedSuitCounts.at(0).second >= STD_HAND_NUM)
    {
        flush = true;
    }

    // Straight
    bool straight = false;
    int rankSize = rankCounts.size();
    if (rankSize >= STD_HAND_NUM)
    {
        for (unsigned int i = 0; i <= rankSize - STD_HAND_NUM; i ++)
        {
            unsigned int j = i;
            while(j < STD_HAND_NUM - 1)
            {
                if (rankPairs.at(j).first - 1 != rankPairs.at(j + 1).first)
                {
                    break;
                }
                j ++;
            }
            if (j == STD_HAND_NUM - 1)
            {
                straight = true;
                break;
            }
        }
    }

    //Flush-straight
    if (straight && flush)
    {
        type = STRAIGHT_FLUSH;
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

    // Three of a kind
    if (sortedRankCounts.at(0).second >= 3)
    {
        type = THREE_OF_A_KIND;
        return;
    }

    // Two Pair
    if (sortedRankCounts.at(0).second == 2 && sortedRankCounts.size() > 1 && sortedRankCounts.at(1).second == 2)
    {
        type = TWO_PAIR;
        return;
    }

    // Pair
    if (sortedRankCounts.at(0).second == 2)
    {
        type = PAIR;
        return;
    }

    // Single
    type = HIGH_CARD;

}

int main()
{
    vector<string> cards{"7s", "2s", "6c", "6h", "8s", "6s"};
    int type{};
    vector<int> cardEncoding;
    analyzeCards(cards, type, cardEncoding);
    cout << "type: " << TYPE_MAP[type] << endl;

}

