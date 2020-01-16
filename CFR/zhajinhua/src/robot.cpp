//
// Created by Administrator on 2020/1/3 0003.
//

#include "robot.h"

bool Robot::isRobot()
{
    return true;
}

Action* Robot::play(const State* state)
{
    auto action = new Action;
    action->type = CALL;
    return action;
}


void Robot::confirmToContinue()
{
    // Nothing to do
}




