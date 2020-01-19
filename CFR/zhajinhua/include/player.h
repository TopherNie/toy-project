//
// Created by Administrator on 2019/12/28 0028.
//

#ifndef TOY_PROJECT_PLAYER_H
#define TOY_PROJECT_PLAYER_H

#include <vector>
#include <string>
#include <state.h>

#include <constants.h>

using namespace std;

class Player
{
public:
    int id;
    string name;
    vector<string> cards;
    int cardsType{};
    vector<int> cardTypeIndexes;
    vector<Action*> history;
    int totalChips{};
    bool isOut{};

    bool operator==(Player *player);

    virtual bool isRobot();
    int getRoundBets();

    virtual Action* play(const State* state);

    virtual void confirmToContinue();

};

#endif //TOY_PROJECT_PLAYER_H
