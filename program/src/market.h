#ifndef MARKET_H
#define MARKET_H
#include <random>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <math.h>
using namespace std;

class Market {
public:
    Market();

    void initialzeMarket(int numberOfAgents, double agentCapital);
    int calculateEquilibriumState();


private:
    int m_numberOfAgents;
    double m_marketCapital;
    double m_averageCapital;
    double *m_agentCaptal;
    double m_agentSavingFactor;
    double m_agentSpendingFactor;
    unsigned long int *m_capitalOccurencies;


    //int **m_transactionLog;

};

#endif // MARKET_H
