//
// Created by Administrator on 2020/1/19 0019.
//

#include "card_analyze.cpp"

int howManyBetter(const vector<string> &baseHoleCards, const vector<string> &boardCards)
{
    auto* baseRes = new CardsRes;
    vector<int> baseWinCardIndexes;
    vector<int> baseWinRanks;
    baseRes->winCardIndexes = baseWinCardIndexes;
    baseRes->winRanks = baseWinRanks;
    baseRes->cards.insert(baseRes->cards.end(), boardCards.begin(), boardCards.end());
    baseRes->cards.insert(baseRes->cards.end(), baseHoleCards.begin(), baseHoleCards.end());

    auto* res = new CardsRes;
    vector<int> winCardIndexes;
    vector<int> winRanks;
    res->winCardIndexes = winCardIndexes;
    res->winRanks = winRanks;
    res->cards.insert(res->cards.end(), boardCards.begin(), boardCards.end());

    int winCount{}, loseCount{}, tieCount{};
    CardsRes* compRes;

    vector<string> cardList;
    for (char s : CARD_SUITS)
    {
        for (char r : CARD_RANKS)
        {
            string card;
            card.append(char2String(r)).append(char2String(s));
            if (find(baseRes->cards.begin(), baseRes->cards.end(), card) == baseRes->cards.end())
            {
                cardList.push_back(card);
            }
        }
    }

    const int cardSize = cardList.size();
    string holeCard0, holeCard1;
    for (int i = 0; i < cardSize; i ++)
    {
        holeCard0 = cardList.at(i);
        res->cards.push_back(holeCard0);
        for (int j = i + 1; j < cardSize; j ++)
        {
            holeCard1 = cardList.at(j);
            res->cards.push_back(holeCard1);
            compRes = compareCards(baseRes, res);
            if (compRes == nullptr)
            {
                tieCount ++;
            } else if (compRes == baseRes){
                winCount ++;
            } else{
                loseCount ++;
            }
            res->cards.pop_back();
            res->winRanks.clear();
            res->winCardIndexes.clear();
            baseRes->winRanks.clear();
            baseRes->winCardIndexes.clear();
        }
        res->cards.pop_back();
    }

    cout << "Win count: " << winCount << endl;
    cout << "Lose count: " << loseCount << endl;
    cout << "Tie count: " << tieCount << endl;

    delete(res);
    delete(baseRes);
    return 0;
}

int main()
{
//    vector<string> baseHoleCards{"5c", "4s"};
//    vector<string> baseBoardCards{"4c", "3d", "2d", "Qd", "Qc"};
    vector<string> baseHoleCards{"Kd", "3h"};
    vector<string> baseBoardCards{"4c", "2d", "2c", "Kc", "7c"};
//    vector<string> baseHoleCards{"Kd", "3h"};
//    vector<string> baseBoardCards{"Ac", "Ad", "Ah", "As", "Kc"};
    howManyBetter(baseHoleCards, baseBoardCards);
}
