//
// Created by Administrator on 2020/1/15 0015.
//

#include <array>

#ifndef TOY_PROJECT_CONSTANTS_H
#define TOY_PROJECT_CONSTANTS_H

#define STD_HAND_NUM 3
#define HOLE_NUM 2
#define BOARD_NUM 2

#define SMALL_BLIND "s"
#define BIG_BLIND "b"
#define FOLD "f"
#define CALL "c"
#define RAISE "r"
#define ALL_IN "a"

#define STREET_MAX_BET_COUNT 3

#define PRE_FLOP 0
#define FLOP 1
#define TURN 2

#define BASIC_BET 1
#define MAX_BET 200

#define TYPE_FOLD -1
#define TYPE_OPPONENT_FOLD 0
#define SINGLE 1
#define PAIR 2
#define STRAIGHT 3
#define FLUSH 4
#define FLUSH_STRAIGHT 5
#define LEOPARD 6

#define NODE_TYPE_FOLD -2
#define NODE_TYPE_CALL -1
#define NODE_TYPE_CHANCE 0
#define NODE_TYPE_RAISE 1     //Any other node

#define INDENT_SYMBOL "\t"

using namespace std;

extern const array<double, 3> BET_RATE;

#endif //TOY_PROJECT_CONSTANTS_H
