//
// Created by Administrator on 2019/12/31 0031.
//

#include <iostream>
#include <round.h>
#include <robot.h>

#define ROUND_NUM 20


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
    auto robot = new Robot;
    round.addPlayer(robot);

    for (unsigned int i = 0; i < ROUND_NUM;  i++)
    {
        round.preFlop();
        round.battle();
        round.settle();
        round.clear();
    }

}

