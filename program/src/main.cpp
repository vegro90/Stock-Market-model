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
    double initialCapital, distributionResolution;
    numberOfAgents = 500;
    initialCapital = 1;
    distributionResolution = 0.01;

    string filename = "testHist.txt";

    ofile.open(filename);
    ofile << numberOfAgents << endl << distributionResolution << endl;
    ofile.close();

    Market market;

    //Initialize market and reach equilibrium
    market.initialzeMarket(numberOfAgents,initialCapital);
    market.initializeTransactionLog();
    market.logEquilibriumState(filename);

    market.setCorrelationStrength(0.0);
    market.setExperienceStrength(0.0);
    market.setAgentSavingFactor(0.0);

    market.initializeDistribution(distributionResolution);

    //Perform simulation
    for (int i = 0; i <1e2; i++) {
        market.runEquilibrium(1e2);
        market.runTransactions(1e4);
        market.resetTransactionLog();
        market.resetMarket();
    }

    //Write to file
    market.writeDistributionToFile(filename);

    return 0;
}

