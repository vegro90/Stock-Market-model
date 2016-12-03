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
    void resetMarket();
    void initializeDistribution(double distributionResolution);
    void resetDistribution();
    void initializeTransactionLog();
    void resetTransactionLog();
    //void calculateEquilibriumState();
    int calculateEquilibriumState(string filename);

    void runEquilibrium(int numberOfCycles);
    void runTransactions(int numberOfCycles);
    void calculateCapitalDistribution(int numberOfCycles, int numberOfTransactions, int distributionResolution);

    void writeDistributionToFile(string filename);
    void writeHeader(string filename);
    void printTransactionLog();

    //SETTERS
    int numberOfAgents() const;
    double marketCapital() const;
    double averageCapital() const;
    double *agentCaptal() const;
    double agentSavingFactor() const;
    double agentSpendingFactor() const;
    unsigned long *capitalOccurencies() const;

    double correlationStrength() const;
    double experienceStrength() const;

    //GETTERS
    void setNumberOfAgents(int numberOfAgents);
    void setMarketCapital(double marketCapital);
    void setAverageCapital(double averageCapital);
    void setAgentCaptal(double *agentCaptal);
    void setAgentSavingFactor(double agentSavingFactor);
    void setAgentSpendingFactor(double agentSpendingFactor);
    void setCapitalOccurencies(unsigned long *capitalOccurencies);

    void setCorrelationStrength(double correlationStrength);
    void setExperienceStrength(double experienceStrength);

private:
    int m_numberOfAgents;
    double m_marketCapital;
    double m_averageCapital;
    double *m_agentCaptal;
    double m_agentSavingFactor;
    double m_agentSpendingFactor;
    unsigned long int *m_capitalDistribution;
    double m_distributionResolution;
    int **m_transactionLog;
    int m_distributionLength;

    double m_correlationStrength;
    double m_experienceStrength;


    //int **m_transactionLog;

};

#endif // MARKET_H
