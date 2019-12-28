//
// Created by Administrator on 2019/12/25 0025.
//

#include <iostream>
#include <card.h>

using namespace std;

int main()
{
    string p1Card, p2Card;
    vector<string> cardList = dealCards(p1Card, p2Card);

    vector<string> testCards{"7s", "6s", "6c", "8s"};
    int type{};
    int maxRank{};
    analyzeCards(testCards, type, maxRank);
    cout << "Type: " << TYPE_MAP[type] << "; " << "maxRank: "  << maxRank << endl;
}
