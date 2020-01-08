//
// Created by Administrator on 2019/12/28 0028.
//

#ifndef TOY_PROJECT_PLAYER_H
#define TOY_PROJECT_PLAYER_H

#include <vector>
#include <array>
#include <string>
#include <tree_node.h>

#define STD_HAND_NUM 3
#define HAND_NUM 4
#define HOLE_NUM 2

#define SMALL_BLIND "s"
#define BIG_BLIND "b"
#define CHECK "k"
#define FOLD "f"
#define CALL "c"
#define RAISE "r"

using namespace std;

extern const array<double, 3> BET_RATE;

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
    int cardsType{};
    vector<int> cardTypeIndexes;
    vector<Action*> history;
    unsigned int totalChips{};
    bool isOut{};

    virtual bool isRobot();
    int getRoundBets();

    virtual Action* play(Node* node);

    bool operator==(Player *player);
};

#endif //TOY_PROJECT_PLAYER_H
