//
// Created by Administrator on 2019/12/15 0015.
//

#include <map>
#include <string>
#include <iostream>

#include "cfr_kuhn.h"
#include "tools.h"

using namespace std;

map<string, Node*> nodeMap;

Node::Node()
{
    cout << "Initialize a node object" << endl;
}

Node::~ Node()
{
    cout << "Destory a node object" << endl;
}

double* Node::getStrategy(double realizationWeight)
{
    double normalizingSum = 0;
    for (int a = 0; a < NUM_ACTIONS; a ++)
    {
        strategy[a] = regretSum[a] > 0 ? regretSum[a] : 0;
        normalizingSum += strategy[a];
    }
    for (int a = 0; a < NUM_ACTIONS; a ++)
    {
        if (normalizingSum > 0)
        {
            strategy[a] /= normalizingSum;
        } else{
            strategy[a] = 1.0 / NUM_ACTIONS;
        }
        strategySum[a] += realizationWeight * strategy[a];
    }
//    cout << oriArrToStr(strategy, NUM_ACTIONS) << endl;
    return strategy;
}

double* Node::getAverageStrategy()
{
    static double avgStrategy[NUM_ACTIONS];
    double normalizingSum = 0;
    for (double s : strategySum)
    {
        normalizingSum += s;
    }
    for (int a = 0; a < NUM_ACTIONS; a ++)
    {
        if (normalizingSum > 0)
        {
            avgStrategy[a] = strategySum[a] / normalizingSum;
        } else{
            avgStrategy[a] = 1.0 / NUM_ACTIONS;
        }
    }
    return avgStrategy;
}


string Node::toString() {
    ostringstream oStr;
    oStr.str("");
    oStr << infoSet << " " << oriArrToStr(getAverageStrategy(), NUM_ACTIONS);
    return oStr.str();
}

void shuffleCards(int* cards, int size)
{
    for (int c1 = size - 1; c1 > 0; c1 --)
    {
        int c2 = getRandom(c1);
        if (c1 != c2)
        {
            int tmp = cards[c1];
            cards[c1] = cards[c2];
            cards[c2] = tmp;
        }
    }
}

double cfr(int cards[], string history, double p0, double p1)
{
    int plays = history.size();
    int player = plays % 2;
    int opponent = 1 - player;

    //Return payoff for terminal states
    if (plays > 1)
    {
        bool terminalPass = history.at(plays - 1) == 'p';
        bool doubleBet = history.substr(plays - 2, plays) == "bb";
        bool isPlayCardHigher = cards[player] > cards[opponent];
        if (terminalPass)
        {
            if (history == "pp")
            {
                return isPlayCardHigher ? 1 : -1;
            } else{
                return 1;
            }
        } else if (doubleBet){
            return isPlayCardHigher ? 2 : -2;
        }
    }

    stringstream ss;
    ss << cards[player];
    string infoSet = ss.str() + history;

    Node* node;
    // Get information set node or create it if nonexistent
    if (!nodeMap.count(infoSet)){
        node = new Node();
        node -> infoSet = infoSet;
        nodeMap[infoSet] = node;
    } else{
        node = nodeMap[infoSet];
    }

    // For each type, recursively call cfr with additional history and probability
    double* strategy = node -> getStrategy(player == 0 ? p0 : p1);
    double  util[NUM_ACTIONS]{};
    double nodeUtil = 0;
    for (int a = 0; a < NUM_ACTIONS; a ++)
    {
        string nextHistory = history + (a == 0 ? "p" : "b");
        // Why minus sign here ? It's about the next type, so it's counter-factual.
        util[a] = player == 0 ? - cfr(cards, nextHistory, p0 * strategy[a], p1) : - cfr(cards, nextHistory, p0, p1 * strategy[a]);
        nodeUtil += (strategy[a] * util[a]);
    }


    // For each type, compute and accumulate counter-factual regret
    for (int a = 0; a < NUM_ACTIONS; a ++)
    {
        double regret = util[a] - nodeUtil;
        node -> regretSum[a] += ((player == 0 ? p1 : p0) * regret);
    }

    return nodeUtil;
}



void train(int iterations)
{
    int cards[CARD_NUM] = {1, 2, 3};
    double util = 0;
    for (int i = 0; i < iterations; i++)
    {
        shuffleCards(cards, CARD_NUM);
        util += cfr(cards, "", 1, 1);
//        for (auto & entry: nodeMap)
//        {
//            cout << entry.first << ": " << oriArrToStr(entry.second -> strategy, NUM_ACTIONS) << endl;
//        }
//        cout << "========================================================================" << endl;
    }
    cout << "Average game value: " << util / iterations << endl;

}

void printNodeMap(map<string, Node*> m)
{
    for (auto &entry : m)
    {
        cout << entry.second -> toString() << endl;
    }
}

void destroyMap(map<string, Node*> m)
{
    auto it = m.begin();
    while (it != m.end())
    {
        delete it -> second;
        it -> second = NULL;
        m.erase(it ++);
    }
}

int main()
{
    cout << "Starting ..." << endl;
    train(100);
    printNodeMap(nodeMap);
    destroyMap(nodeMap);
}