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

    void initialzeMarket(int numberOfAgents, double agentInitalCapital);
    void simulateTransactions(int numberOfTransactions,int equilibriumNumberOfTransactions,  double smallesTransactionSize );

    void writeLogToFile(string fileName);

    int numberOfAgents() const;
    double marketCapital() const;
    double *agent() const;
    long int *transactionLog() const;

    void setNumberOfAgents(int numberOfAgents);
    void setMarketCapital(double marketCapital);
    void setAgents(double *agent);
    void setTransactionLog(long int *transactionLog);

private:
    int m_numberOfAgents;
    double m_marketCapital;
    double *m_agents;
    long int *m_CapitalOccurencies;


};

#endif // MARKET_H
