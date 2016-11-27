//#include "mpi.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <math.h>
#include "market.h"

using namespace std;

ofstream ofile;

int main(int argc, char *argv[]) {
    Market market = Market();
    market.initialzeMarket(50 , 10);
    cout << "Number of Agents: "<< market.numberOfAgents() << endl;
    cout << "Market capital: "<< market.marketCapital() << endl;

    for ( int i = 1; i <= market.numberOfAgents(); i++) {
        cout << "agent "<< i <<": " << market.agent()[i] << endl;
    }


    market.simulateTransactions(100000000,0.01);

    for ( int i = 1; i <= market.numberOfAgents(); i++) {
        cout << "agent "<< i <<": " << market.agent()[i] << endl;
    }
    double sum = 0;
    for ( int i = 1; i <= market.numberOfAgents(); i++) {
        sum += market.agent()[i];
    }
    cout << "sum : " << sum << endl;
    market.writeLogToFile("testHist");

    return 0;
}

