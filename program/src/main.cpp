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
    int numberOfAgents = 500;
    double initialCapital = 1;
    Market market;

//    string filename = "equilibriumtestForSavings.txt";

    //Initialize market and reach equilibrium
//    for (int N = 100; N < 600; N+=100) {
//        string filenameN = filename;
//        filenameN.append(to_string(N));
//        for (int i = 0; i < 10000; i++) {
//        market.initialzeMarket(numberOfAgents,initialCapital);
//        market.logEquilibriumState(filenameN);
//        }
//    }

    //Initialize market for histogram and equilibrium (task A)
    int numbeOfCycles = 1000;
    double capitalIntervall = 0.01;
    string filename = "taskA_histogram.txt";

    market.initialzeMarket(numberOfAgents, initialCapital);
    market.runTransactionsWithHistogram(numbeOfCycles, capitalIntervall, filename);


    //Initialize market with saving for equilibrium tests (task C)
//    int numberOfCycles = 1000;
//    double savingFactor = 0.5;
//    string filename = "equilibriumtestForSavings05.txt";
//    market.initialzeMarket(numberOfAgents,initialCapital);
//    market.runTransactionsWithSavings(numberOfCycles,savingFactor,filename);


    return 0;
}

