//
// Created by Administrator on 2019/12/12 0012.
//

#include <random>
#include <iostream>

#define ROCK 0
#define PAPER 1
#define SCISSORS 2
#define NUM_ACTIONS 3

using namespace std;

double regretSum[NUM_ACTIONS];
double strategy[NUM_ACTIONS];
double strategySum[NUM_ACTIONS];
double oppStrategy[] = {0.4, 0.3, 0.3};

default_random_engine e;
uniform_real_distribution<double > u(0.0, 1.0);

double getRandom(int n)
{
    double re =  u(e);
    return re;
}

void showArrEle(double* arr, int size)
{
    if (size > 0)
    {
        for (int i = 0; i < size; i ++)
        {
            cout << *(arr + i) << " ";
        }
        cout << endl;
    }

}

/**
 * Get probability for each action.
 * @return A strategy vector
 */
void setStrategy()
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
        strategySum[a] += strategy[a];
    }
}


int getAction(double strategy[])
{
    double r = getRandom(1);
    int a = 0;
    double cumulativeProbability = 0;
    while (a < NUM_ACTIONS - 1)
    {
        cumulativeProbability += strategy[a];
        if (r < cumulativeProbability)
        {
            break;
        }
        a ++;
    }
    return a;
}

void train(int iterations)
{
    double actionUtility[NUM_ACTIONS];
    for (int i = 0; i < iterations; i ++)
    {
        // Get regret-matched mixed-strategy actions
        setStrategy();
        int myAction = getAction(strategy);
        int otherAction = getAction(oppStrategy);

        // Compute action utilities
        actionUtility[otherAction] = 0;
        actionUtility[otherAction == NUM_ACTIONS - 1 ? 0: otherAction + 1] = 1;
        actionUtility[otherAction == 0 ? NUM_ACTIONS - 1: otherAction - 1] = -1;

        // Accumulate action regrets
        for (int a = 0; a < NUM_ACTIONS; a ++)
        {
            regretSum[a] = actionUtility[a] - actionUtility[myAction];
        }
        int size = sizeof(regretSum) / sizeof(double);
        showArrEle(regretSum, size);
    }
}

double* getAverageStrategy()
{
    static double avgStrategy[NUM_ACTIONS];
    double normalizingSum = 0;
    for (int a = 0; a < NUM_ACTIONS; a ++)
    {
        normalizingSum += strategySum[a];
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

int main()
{
    train(20000000);
    double* avgStrategy;
    avgStrategy = getAverageStrategy();
    showArrEle(avgStrategy, NUM_ACTIONS);
}
