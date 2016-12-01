#ifndef MARKET_H
#define MARKET_H
#include <random>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
using namespace std;

class Market {
public:
    Market();
    Market(int numberOfAgents, double agentCapital);
    void initialzeMarket(int numberOfAgents, double agentCapital);
    void calculateEquilibriumState();

    void runTransactions(int numberOfTransactions);
    void calculateCapitalDistribution(int numberOfCycles, int numberOfTransactions, int distributionResolution);

    //SETTERS
    int numberOfAgents() const;
    double marketCapital() const;
    double averageCapital() const;
    double *agentCaptal() const;
    double agentSavingFactor() const;
    double agentSpendingFactor() const;
    unsigned long *capitalOccurencies() const;

    //GETTERS
    void setNumberOfAgents(int numberOfAgents);
    void setMarketCapital(double marketCapital);
    void setAverageCapital(double averageCapital);
    void setAgentCaptal(double *agentCaptal);
    void setAgentSavingFactor(double agentSavingFactor);
    void setAgentSpendingFactor(double agentSpendingFactor);
    void setCapitalOccurencies(unsigned long *capitalOccurencies);

private:
    int m_numberOfAgents;
    double m_marketCapital;
    double m_averageCapital;
    double *m_agentCaptal;
    double m_agentSavingFactor;
    double m_agentSpendingFactor;
    unsigned long int *m_capitalDistribution;
    double m_distributionResolution;


    //int **m_transactionLog;

};

#endif // MARKET_H
