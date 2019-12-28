//
// Created by Administrator on 2019/12/15 0015.
//

#ifndef TOY_PROJECT_CFR_KUHN_H
#define TOY_PROJECT_CFR_KUHN_H

#include <string>

using namespace std;

#define PASS 0
#define BET 1
#define NUM_ACTIONS 2
#define CARD_NUM 3


struct Node
{
    string infoSet;
    double regretSum[NUM_ACTIONS]{};
    double strategy[NUM_ACTIONS]{};
    double strategySum[NUM_ACTIONS]{};

    Node();
    ~ Node();

    /**
     * What is RealizationWeight ?
     * @param realizationWeight What is it?
     * @return
     */
    double* getStrategy(double realizationWeight);
    double* getAverageStrategy();
    string toString();
};

void printNodeMap(map<string, Node> m);

#endif //TOY_PROJECT_CFR_KUHN_H

