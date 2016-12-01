//#include "mpi.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <random>
#include <math.h>
#include "market.h"

using namespace std;

ofstream ofile;

int main(int argc, char *argv[]) {
    int numberOfAgents;
    double initialCapital;
    numberOfAgents = 500;
    initialCapital = 1;
    string filename = "testHist.txt";
    Market market;

    //Initialize market and reach equilibrium
    market.initialzeMarket(numberOfAgents,initialCapital);
    market.logEquilibriumState(filename);
    market.initializeDistribution(0.01);
    for (int i = 0; i <1e3; i++) {
        market.runTransactions(1e3);
    }
    market.writeDistributionToFile(filename);




    return 0;
}

