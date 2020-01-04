//
// Created by Administrator on 2019/12/28 0028.
//

#ifndef TOY_PROJECT_PLAYER_H
#define TOY_PROJECT_PLAYER_H

#include <vector>
#include <string>

#define PLAYER_0 0
#define PLAYER_1 1

#define SMALL_BLIND 's'
#define BIG_BLIND 'b'
#define CHECK 'k'
#define FOLD 'f'
#define CALL 'c'
#define RAISE 'r'

using namespace std;

struct Action
{
    char type;
    int bets;
};

struct Player
{
    int id;
    bool isRobot;
    vector<string> cards;
    vector<Action*> history;
    int totalChips;
    bool isOut;

    int roundBets();

    virtual Action* play();

    bool operator==(Player *player);
};

#endif //TOY_PROJECT_PLAYER_H
