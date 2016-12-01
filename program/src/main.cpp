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
    string filename = "equilibriumtest";
    Market market;

    //Initialize market and reach equilibrium
    for (int N = 100; N < 600; N+=100) {
        string filenameN = filename;
        filenameN.append(to_string(N));
        for (int i = 0; i < 10000; i++) {
        market.initialzeMarket(numberOfAgents,initialCapital);
        market.logEquilibriumState(filenameN);
        }
    }



    return 0;
}

