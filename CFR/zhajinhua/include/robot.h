//
// Created by Administrator on 2020/1/3 0003.
//

#ifndef TOY_PROJECT_ROBOT_H
#define TOY_PROJECT_ROBOT_H

#include <player.h>

struct Robot: Player{
    bool isRobot() override;
    Action* play(Node* node) override;
    void confirmToContinue() override;
};

#endif //TOY_PROJECT_ROBOT_H
