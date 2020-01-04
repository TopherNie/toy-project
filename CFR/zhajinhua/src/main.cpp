//
// Created by Administrator on 2019/12/31 0031.
//

#include <iostream>
#include <round.h>


using namespace std;

void testCard()
{
    vector<string> testCards{"7s", "2s", "6c", "6h"};
    int type{};
    int maxRank{};
    analyzeCards(testCards, type, maxRank);
    cout << "Type: " << TYPE_MAP[type] << "; " << "maxRank: "  << maxRank << endl;
}

int main()
{
    Round round;
    auto you = new Player;
    round.addPlayer(you);
    round.preFlop();
    round.battle();
}

