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
    vector<pair<int, Action*>> currentStreetUserActions = state->streetActionMap.at(state->currentStreet);
    if (currentStreetUserActions.empty() || currentStreetUserActions.at(currentStreetUserActions.size() - 1).second->type == CHECK)
    {
        action->type = CHECK;
    } else{
        action->type = CALL;
    }
    return action;
}


void Robot::confirmToContinue()
{
    // Nothing to do
}


