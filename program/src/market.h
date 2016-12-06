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
    void monteCarloCycle();

    int calculateEquilibriumState(string filename);


    void runEquilibrium(int numberOfCycles);
    void runTransactions(int numberOfCycles);
    void calculateCapitalDistribution(int numberOfCycles, int numberOfTransactions, int distributionResolution);

    void writeDistributionToFile(string filename);
    void writeHeader(string filename);
    void printTransactionLog();
    void createFileName();

    //SETTERS
    int numberOfAgents() const;
    double distributionResolution() const;
    double marketCapital() const;
    double averageCapital() const;
    double *agentCaptal() const;
    double agentSavingFactor() const;
    double agentSpendingFactor() const;
    double equalityLimit() const;
    unsigned long *capitalOccurencies() const;

    double correlationStrength() const;
    double experienceStrength() const;

    //GETTERS
    void setNumberOfAgents(int numberOfAgents);
    void setDistributionResolution(double distributionResolution);
    void setMarketCapital(double marketCapital);
    void setAverageCapital(double averageCapital);
    void setAgentCaptal(double *agentCaptal);
    void setAgentSavingFactor(double agentSavingFactor);
    void setAgentSpendingFactor(double agentSpendingFactor);
    void setEqualityLimit(double equalityLimit);
    void setCapitalOccurencies(unsigned long *capitalOccurencies);

    void setCorrelationStrength(double correlationStrength);
    void setExperienceStrength(double experienceStrength);


private:
    //Market variables
    int m_numberOfAgents;
    unsigned long int *m_capitalDistribution;
    double m_distributionResolution;
    int m_distributionLength;

    //Capital values
    double m_marketCapital;
    double m_averageCapital;
    double *m_agentCaptal;

    //Saving fraction
    double m_agentSavingFactor;
    double m_agentSpendingFactor;


    //Financial equality
    double m_correlationStrength;
    double m_equalityLimit;

    //Financial history
    unsigned long int **m_transactionLog;
    double m_experienceStrength;
    unsigned long int *m_transactionLogNorm;

    string m_fileName;
};

#endif // MARKET_H
