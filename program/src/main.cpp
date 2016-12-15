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
    int numberOfAgents, equilibriumStateMax,equilibriumState, experiments, cycles;
    double initialCapital, distributionResolution;
    double saving, correlation, experience;
    equilibriumState = 0;
    equilibriumStateMax = 0;
    string filename;
    distributionResolution = 0.01;
    if (argc > 8) {
        filename = argv[1];
        numberOfAgents = atoi(argv[2]);
        initialCapital = atof(argv[3]);
        saving = atof(argv[4]);
        correlation = atof(argv[5]);
        experience = atof(argv[6]);
        cycles = atoi(argv[7]);
        experiments = atoi(argv[8]);
    } else {
        cout << "*************** ERROR ***************" << endl;
        cout << "!!! Bad usage !!! \nadd following input arguments:" << endl;
        cout << "- Filename " << endl;
        cout << "- Number of agents" << endl;
        cout << "- Initial capital" << endl;
        cout << "- Saving rate" << endl;
        cout << "- Correlation factor" << endl;
        cout << "- Experience factor" << endl;
        cout << "- Monte Carlo cycles per experiment" << endl;
        cout << "- Number of experiments" << endl;
        cout << "*************************************" << endl;
        cout << "e.g. \"./src fileName 500 1 0.5 0.2 0.1 1000 1000\"" << endl;
        exit(1);
    }

    Market market;

    //Initialize market and reach equilibrium

    market.initialzeMarket(numberOfAgents,initialCapital);
    market.initializeTransactionLog();

    market.setCorrelationStrength(correlation);
    market.setExperienceStrength(experience);
    market.setAgentSavingFactor(saving);


    //Calculate a safe equilibrium criteria
    market.writeHeader(filename+"_EqHist.txt");
    for (int i = 0; i < 1e3; i++) {
        equilibriumState = market.calculateEquilibriumState(filename);
        market.resetMarket();
        market.resetTransactionLog();
        if (equilibriumState > equilibriumStateMax) {
            equilibriumStateMax = equilibriumState;
        }
    }
    market.initializeDistribution(distributionResolution);

   //Perform simulation
    for (int i = 0; i < experiments; i++) {
        market.resetTransactionLog();
        market.resetMarket();
        market.runEquilibrium(equilibriumStateMax);
        market.runTransactions(cycles);
    }

    //Write to file
    market.writeDistributionToFile(filename);

    return 0;
}

