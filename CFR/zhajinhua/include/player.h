//
// Created by Administrator on 2019/12/28 0028.
//

#ifndef TOY_PROJECT_PLAYER_H
#define TOY_PROJECT_PLAYER_H

#include <vector>
#include <string>

#define PLAYER_0 0
#define PLAYER_1 1

#define SMALL_BLIND "s"
#define BIG_BLIND "b"
#define CHECK "k"
#define FOLD "f"
#define CALL "c"
#define RAISE "r"

using namespace std;

struct Action
{
    string type;
    int bets{};
    string toString();
};

struct Player
{
    int id;
    string name;
    vector<string> cards;
    int cardsType;
    vector<Action*> history;
    unsigned int totalChips;
    bool isOut;

    virtual bool isRobot();
    int getRoundBets();
    Action* getLastAction();

    virtual Action* play();

    bool operator==(Player *player);
};

#endif //TOY_PROJECT_PLAYER_H
