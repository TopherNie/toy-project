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
double oppRegretSum[NUM_ACTIONS];
double oppStrategySum[NUM_ACTIONS];
double oppStrategy[NUM_ACTIONS];

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
    double oppNormalizingSum = 0;
    for (int a = 0; a < NUM_ACTIONS; a ++)
    {
        strategy[a] = regretSum[a] > 0 ? regretSum[a] : 0;
        normalizingSum += strategy[a];
        oppStrategy[a] = oppRegretSum[a] > 0 ? oppRegretSum[a] : 0;
        oppNormalizingSum += oppStrategy[a];
    }
    for (int a = 0; a < NUM_ACTIONS; a ++)
    {
        if (normalizingSum > 0)
        {
            strategy[a] /= normalizingSum;
        } else{
            strategy[a] = 1.0 / NUM_ACTIONS;
        }
        if (oppNormalizingSum > 0)
        {
            oppStrategy[a] /= oppNormalizingSum;
        } else{
            oppStrategy[a] = 1.0 / NUM_ACTIONS;
        }
        strategySum[a] += strategy[a];
        oppStrategySum[a] += oppStrategy[a];
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

void setUtility(double *actionUtility, int otherAction)
{
    // Compute action utilities
    actionUtility[otherAction] = 0;
    actionUtility[otherAction == NUM_ACTIONS - 1 ? 0: otherAction + 1] = 1;
    actionUtility[otherAction == 0 ? NUM_ACTIONS - 1: otherAction - 1] = -1;
}

void train(int iterations)
{
    double actionUtility[NUM_ACTIONS];
    double oppActionUtility[NUM_ACTIONS];
    for (int i = 0; i < iterations; i ++)
    {
        // Get regret-matched mixed-strategy actions
        setStrategy();
        int myAction = getAction(strategy);
        int oppAction = getAction(oppStrategy);
        setUtility(actionUtility, oppAction);
        setUtility(oppActionUtility, myAction);

        // Accumulate action regrets
        for (int a = 0; a < NUM_ACTIONS; a ++)
        {
            regretSum[a] = actionUtility[a] - actionUtility[myAction];
            oppRegretSum[a] = oppActionUtility[a] - oppActionUtility[oppAction];
        }
//        cout << "I:   ";
//        showArrEle(strategySum, NUM_ACTIONS);
//        cout << "Opponent:    ";
//        showArrEle(oppStrategySum, NUM_ACTIONS);
    }
}

double* getAverageStrategy(double *strategySum)
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
    train(1000);
    double *avgStrategy, *oppAvgStrategy;
    avgStrategy = getAverageStrategy(strategySum);
    oppAvgStrategy = getAverageStrategy(oppStrategySum);
    cout << "=============== Average Strategy ===============" << endl;
    showArrEle(avgStrategy, NUM_ACTIONS);
    cout << "=============== Opponent average Strategy ===============" << endl;
    showArrEle(oppAvgStrategy, NUM_ACTIONS);
}
