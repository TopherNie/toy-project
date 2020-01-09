//
// Created by Administrator on 2019/12/31 0031.
//

#include <iostream>
#include <round.h>
#include <robot.h>
#include <tools.h>

#define ROUND_NUM 5


using namespace std;

void testCard()
{
    vector<string> testCards{"7s", "2s", "6c", "6h"};
    int type{};
    vector<int> winRanks;
    vector<int> winCardIndexes(testCards.size());
    analyzeCards(testCards, type, winRanks, winCardIndexes);
    cout << "Type: " << TYPE_MAP[type] << "; " << "winRanks: "  << vecToString(winRanks) << endl;
}

int main()
{
    Round round;
    auto you = new Player;
    you->name = "You";
    round.addPlayer(you);
    auto robot = new Robot;
    robot->name = "Robot";
    round.addPlayer(robot);

    for (unsigned int i = 0; i < ROUND_NUM;  i++)
    {
        round.prepare();
        round.battle();
        round.settle();
        round.clear();
    }

}

