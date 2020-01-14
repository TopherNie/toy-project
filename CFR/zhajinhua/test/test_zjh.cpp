//
// Created by Administrator on 2020/1/14 0014.
//

#include <card.h>
#include <tools.h>

void testCardAnalyze()
{
    vector<string> cards_1{"7c", "6d", "4h", "4s"};
    int type{};
    vector<int> winRanks_1{};
    vector<int> winCardIndexes_1{};
    analyzeCards(cards_1, type, winRanks_1, winCardIndexes_1);
    cout << vecToString(winRanks_1) << endl;
}

int main()
{
    testCardAnalyze();
}
