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
    string filename;
    int cycles, equilibrium;
    int agents;
    double initialCapital;
    if(argc>5){
        filename = argv[1];
        agents = atoi(argv[2]);
        initialCapital = atof(argv[3]);
        equilibrium = atoi(argv[4]);
        cycles = atoi(argv[5]);
    } else {
        filename = "testrun";
        cycles = 1e5;
        agents = 50;
        equilibrium = 1e4;
        initialCapital = 1;
    }
    Market market = Market();
    market.initialzeMarket(agents, initialCapital);
    cout << "Number of Agents: "<< market.numberOfAgents() << endl;
    cout << "Market capital: "<< market.marketCapital() << endl;

//    for ( int i = 1; i <= market.numberOfAgents(); i++) {
//        cout << "agent "<< i <<": " << market.agent()[i] << endl;
//    }

    market.simulateTransactions(cycles,equilibrium, 0.01);

//    for ( int i = 1; i <= market.numberOfAgents(); i++) {
//        cout << "agent "<< i <<": " << market.agent()[i] << endl;
//    }
    double sum = 0;
    for ( int i = 1; i <= market.numberOfAgents(); i++) {
        sum += market.agent()[i];
    }
//    cout << "sum : " << sum << endl;
    market.writeLogToFile(filename);

    return 0;
}

