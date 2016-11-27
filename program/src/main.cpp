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
    int cycles, equilibrium;
    int agents;
    double initialCapital;
    if(argc>4){
        agents = atoi(argv[1]);
        initialCapital = atof(argv[2]);
        equilibrium = atoi(argv[3]);
        cycles = atoi(argv[4]);
    } else {
        cycles = 1e5;
        agents = 50;
        equilibrium = 1e2;
        initialCapital = 10;
    }
    Market market = Market();
    market.initialzeMarket(agents, initialCapital);
    cout << "Number of Agents: "<< market.numberOfAgents() << endl;
    cout << "Market capital: "<< market.marketCapital() << endl;

    for ( int i = 1; i <= market.numberOfAgents(); i++) {
        cout << "agent "<< i <<": " << market.agent()[i] << endl;
    }


    market.simulateTransactions(cycles,equilibrium, 0.01);

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

